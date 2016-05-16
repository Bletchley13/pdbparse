#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/stat.h>

#include "msf.h"

MSF* MsfOpen (char *szFileName);

void hexdump(void* p, int len)
{
    int i;
    for( i = 0; i < len; i++ )
    {
        printf("%02x ", *(unsigned char*)(p+i));
        if( (i+1) % 16 == 0)
        { 
            printf("\n");
        }
    }
    printf("\n");
}

void dump_MSF_HDR (PMSF_HDR hdr)
{
    int i;
    printf("sz_magic %s\n", hdr->sz_magic);
    printf("dw_page_size %u\n", hdr->dw_page_size);
    printf("dw_fpm_page %u\n", hdr->dw_fpm_page);
    printf("dw_page_count %u\n", hdr->dw_page_count);
    printf("dw_root_size %u\n", hdr->dw_root_size);
    printf("dw_reserved %u\n", hdr->dw_reserved);
    //prinf("dw_page_size %lu\n", hdr->dw_page_size);
    for(i=0;i<0x49;i++)
    {
        printf("dw_root_pointers %d %u\n", i, hdr->dw_root_pointers[i]);
    }
}

void dump_MSF_STREAM(PMSF_STREAM pstream)
{
    int i;
    printf("iStreamNumber %lu\n", pstream->iStreamNumber);
    printf("uStreamSize %lu\n", pstream->uStreamSize);
    printf("nStreamPages %lu\n", pstream->nStreamPages);
    printf("pStreamData\n");
    for(i=0;i<20;i++)
    {
        printf("%02x ", *(unsigned char*)(pstream->pStreamData+i));
    }
}

//
// All streams are loaded when MSF is being opened.
// This routine just searches for the pointer of loaded stream.
// If there is no stream with the supplied number, the function returns NULL.
// Optionally, it returns stream size (in bytes) in the last parameter.
//

void* MsfReferenceStream (MSF* msf, uint32_t iStreamNumber, size_t *uStreamSize)
{
        MSF_STREAM *s = &msf->pLoadedStreams[iStreamNumber];
        void* pData = s->pStreamData;

        if (pData != NULL)
        {
                //TODO: Move InterlockedExchange to linux
                //InterlockedExchangeAdd (&s->ReferenceCount, 1);

                //if (ARGUMENT_PRESENT (uStreamSize))
                *uStreamSize = s->uStreamSize;
        }

        return pData;
}

//
// Get the array of page indices for the specified stream.
// NB: this function does not have the return value. So, if
// the specified stream does not contain any pages, the pointer
// still will be returned. In this case, you should not try to
// dereference it - these pages are the pages of the NEXT stream.
//

void MsfGetStreamPointers (MSF* msf, uint32_t iStreamNumber, uint32_t** pdwPointers)
{
        int i;
        uint32_t *StreamPointers = &msf->Root->dwStreamSizes[msf->Root->dwStreamCount];

        uint32_t j = 0;
        for (i=0; i<iStreamNumber; i++)
        {
                uint32_t nPages = STREAM_SPAN_PAGES (msf, msf->Root->dwStreamSizes[i]);

                j += nPages;
        }

        *pdwPointers = &StreamPointers[j];
}


//
// Caller supplies pointer to an array of page indices, and number of pages.
// This routine tries to load the corresponding pages from MSF file to the
//  memory and returns pointer to it.
// This is an internal routine.
//
static void* MsfLoadPages (MSF* msf, uint32_t *pdwPointers, size_t nPages)
{
        unsigned long i=0;
        void* Data = calloc(nPages * msf->hdr->dw_page_size, 1);
        if (Data != NULL)
        {
                for (i=0; i<nPages; i++)
                {
                        void* Page = PAGE(msf, pdwPointers[i]);
                        size_t Offset = msf->hdr->dw_page_size * i;

                        memcpy ((uint8_t*)Data + Offset, Page, msf->hdr->dw_page_size);
                }
        }

        return Data;
}


//
// This function tries to load stream from MSF with the specified number.
// On success, return value is a handle to loaded stream.
// On error, return value is 0.
// Therefore, you should not use this routine, 'cause all streams are loaded
//  in MsfOpen() and you should just reference them by MsfReferenceStream/MsfReferenceStreamByType call.
//

MSF_STREAM* MsfLoadStream (MSF* msf, uint32_t iStreamNumber)
{
        MSF_STREAM* stream = &msf->pLoadedStreams[iStreamNumber];
        if (stream != NULL)
        {
                stream->msf = msf;
                stream->iStreamNumber = iStreamNumber;
                stream->ReferenceCount = 1;
                stream->uStreamSize = msf->Root->dwStreamSizes[iStreamNumber];

                if (stream->uStreamSize == spnNil)
                {
                        stream->pStreamData = NULL;
                        stream->nStreamPages = 0;
                        stream->pdwStreamPointers = NULL;
                        return stream;
                }

                stream->nStreamPages = STREAM_SPAN_PAGES (msf, stream->uStreamSize);

                MsfGetStreamPointers (msf, iStreamNumber, &stream->pdwStreamPointers);

                stream->pStreamData = (void*)MsfLoadPages (msf, stream->pdwStreamPointers, stream->nStreamPages);

                if (stream->pStreamData != NULL)
                {
                        dump_MSF_STREAM(stream);
                        return stream;
                }

                memset (stream, 0, sizeof(MSF_STREAM));
        }
        return NULL;
}

MSF* MsfOpen (char *szFileName)
{
        size_t Size;
        int fd;
        struct stat sb;
        //void* Map = MapExistingFile(szFileName, MAP_READ, NULL, &Size);
          
        fd=open(szFileName, O_RDONLY);

        fstat(fd, &sb);
        printf("Size: %lu\n", (uint64_t)sb.st_size);

        void* Map = mmap( NULL, sb.st_size , PROT_READ, MAP_SHARED , fd , 0  ); 
        //hexdump(Map, 100); 

        if (Map != NULL)
        {
                
                MSF* msf = (MSF*)calloc(sizeof(MSF), 1);

                if (msf != NULL)
                {
                        msf->MapV = Map;
                        dump_MSF_HDR(msf->hdr);
                        printf("sz_magic %s\n", msf->hdr->sz_magic);
                        hexdump(msf->hdr, 100);
                                          
                        msf->MsfSize = sb.st_size;
                       
                        printf("msf->hdr->dw_root_size %u\n", msf->hdr->dw_root_size);

                        msf->RootPages = STREAM_SPAN_PAGES (msf, msf->hdr->dw_root_size);
                        msf->RootPointersPages = STREAM_SPAN_PAGES (msf, msf->RootPages*sizeof(unsigned long));

                        printf("msf->RootPages %lu\n", msf->RootPages);
                        printf("msf->RootPointersPages %lu\n", msf->RootPointersPages);

                        msf->pdwRootPointers = (uint32_t*) MsfLoadPages (msf, msf->hdr->dw_root_pointers, msf->RootPointersPages);

                        if (msf->pdwRootPointers != NULL)
                        {
                                msf->Root = (MSF_ROOT*) MsfLoadPages (msf, msf->pdwRootPointers, msf->RootPages);

                                if (msf->Root != NULL)
                                {
                                        msf->pLoadedStreams = (MSF_STREAM*) calloc (sizeof(MSF_STREAM), msf->Root->dwStreamCount);
                                        if (msf->pLoadedStreams != NULL)
                                        {
                                                return msf;
                                        }
                                        free (msf->Root);
                                }
                                free (msf->pdwRootPointers);
                        }

                        free (msf);
                }

                //UnmapViewOfFile (Map);
                //*/
        }

        return NULL;
}



/*
int main(int argc, char *argv[])
{
    MsfOpen(argv[1]);
}*/
