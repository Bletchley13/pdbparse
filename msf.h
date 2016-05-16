#ifndef __MSF_H__
#define __MSF_H__

#include <stdint.h>
#include <stdbool.h>



//
// Useful macroses.
//

#define ALIGN_DOWN(x, align) ((x) & ~(align-1))
#define ALIGN_UP(x, align) (((x) & (align-1))?ALIGN_DOWN(x,align)+align:(x))



#define PAGE(msf,x) (msf->MapB + msf->hdr->dw_page_size * (x))
#define STREAM_SPAN_PAGES(msf,size) (ALIGN_UP(size,msf->hdr->dw_page_size)/msf->hdr->dw_page_size)

#define spnNil ((int32_t)-1)


// MSF File Header
typedef struct MSF_HDR
{
        char sz_magic[32];          // 0x00  Signature
        uint32_t dw_page_size;          // 0x20  Number of bytes in the pages (i.e. 0x400)
        uint32_t dw_fpm_page;           // 0x24  FPM (free page map) page (i.e. 0x2)
        uint32_t dw_page_count;         // 0x28  Page count (i.e. 0x1973)
        uint32_t dw_root_size;          // 0x2c  Size of stream directory (in bytes; i.e. 0x6540)
        uint32_t dw_reserved;          // 0x30  Always zero.
        uint32_t dw_root_pointers[0x49];// 0x34  Array of pointers to root pointers stream.
} MSF_HDR, *PMSF_HDR;

//
// MSF_HDR::dwRootPointers -> Root Directory Pointers -> Root Directory (stream pointers) -> Stream data
//

// Free Page Map
typedef struct MSF_FPM
{
        uint32_t iwMax;  //DWORD
        uint32_t iwRover;
        long cbPg;
        bool fBigMsf;
        uint8_t reserved1;
        uint16_t reserved2;
        struct {
                uint32_t rgt;
                uint32_t itMac;
                uint32_t itMax;
        } rgw;
        uint32_t wFill;
} *PMSF_FPM;

typedef struct MSF_ROOT
{
        uint32_t dwStreamCount;
        uint32_t dwStreamSizes[];
} MSF_ROOT, *PMSF_ROOT;

struct MSF_STREAM;
typedef struct MSF_STREAM MSF_STREAM;

typedef struct MSF
{
        union {
                MSF_HDR* hdr;
                void* MapV;
                unsigned char* MapB;
        };
        unsigned long MsfSize;
        unsigned long RootPages;
        unsigned long RootPointersPages;
        uint32_t *pdwRootPointers;
        MSF_ROOT *Root;
        MSF_STREAM *pLoadedStreams;

        MSF_HDR HdrBackStorage;
} MSF, *PMSF;

typedef struct MSF_STREAM
{
        MSF* msf;
        unsigned long iStreamNumber;
        long ReferenceCount;
        void* pStreamData;
        unsigned long uStreamSize;
        unsigned long nStreamPages;
        uint32_t *pdwStreamPointers;
} MSF_STREAM, *PMSF_STREAM;

MSF* MsfOpen (char *szFileName);
void* MsfReferenceStream (MSF* msf, uint32_t iStreamNumber, size_t *uStreamSize);

#endif
