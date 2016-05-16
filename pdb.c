
#include <stdlib.h>
#include <stdio.h>

#include "msf.h"
#include "pdb.h"

//
// Try to open PDB (with EXACT path) routine and validate its signature (GUID and age supplied).
// Return Value: pointer to PDB handle on success, NULL otherwise.
//  You should treat this value as opaque, but in rare cases you can safely read PDB structure (NOT modify it).
// For example, you can access symbol table : (pdb->Symd->SymRecs).
// NB: You can supply NULL in guidSig and age, in this case no checks will be performed.
// Also, you can use PdbOpen(), which does the same.
// NB2: No search if performed, szPdbFileName should have the EXACT CORRECT path to pdb file. Otherwise, function fails.
//

//PPDB PdbOpenValidate (char *szPdbFileName, GUID* guidSig OPTIONAL, DWORD age OPTIONAL)
PPDB PdbOpenValidate (char *szPdbFileName, uint32_t age)
{
        PPDB pdb;
        int i;

        // Create PDB descriptor
        pdb = (PPDB) calloc (sizeof(PDB), 1);
        if (pdb != NULL)
        {
                // Open file
                pdb->msf = MsfOpen (szPdbFileName);
                
                if (pdb->msf != NULL)
                {
                        
                        // Load all streams.
                        for (i=0; i<pdb->msf->Root->dwStreamCount; i++)
                        {
                                printf("stream %d\n", i);
                                MsfLoadStream (pdb->msf, i);
                        }
 
                        /* 
                        template <class T>
                        BOOL MsfReferenceStreamType (MSF* msf, ULONG iStreamNumber, MSF_STREAM_REF<T> *streamRef)
                        {
                            return ((streamRef->Data = (T*) MsfReferenceStream (msf, iStreamNumber, &streamRef->Size)) != NULL);
                        }
 
                        MsfReferenceStreamType (pdb->msf, PDB_STREAM_PDB, &pdb->pdb);
                        MsfReferenceStreamType (pdb->msf, PDB_STREAM_DBI, &pdb->dbi);

                        */
 
                        pdb->pdb.Data = MsfReferenceStream(pdb->msf, PDB_STREAM_PDB, &(pdb->pdb.Size)); 
                        pdb->dbi.Data = MsfReferenceStream(pdb->msf, PDB_STREAM_DBI, &(pdb->dbi.Size));
 
                        /*
                        if (ARGUMENT_PRESENT (guidSig))
                        {
                                if (pdb->pdb.Data->sig70 != *guidSig)
                                {
                                        // GUID mismatch.
                                        PdbClose (pdb);
                                        PdbSetLastError (PDBERR_SIGNATURE_MISMATCH);
                                        return NULL;
                                }

                                if (pdb->pdb.Data->pdbstream.age < age)
                                {
                                        // age mismatch.
                                        PdbClose (pdb);
                                        PdbSetLastError (PDBERR_PDB_TOO_OLD);
                                        return NULL;
                                }

                                // verified.
                        }
                        */

                        // Load symbol information from PDB
                       
                        pdb->Symd = SYMLoadSymbols (pdb->msf);

                        if (pdb->Symd != NULL)
                        {
                                //pdb->szPdbFileName = (char*) halloc (MAX_PATH);
                                //GetFullPathName (szPdbFileName, MAX_PATH-1, pdb->szPdbFileName, 0);

                                // all ok!
                                // we are ready to return new handle..

                                // .. but we have to initialize GSI
                                GSIInit (pdb->Symd);

                                // done! return the handle.
                                return pdb;
                        }

                        /*
                        PdbSetLastError (PDBERR_NO_SYMBOL_INFORMATION);
                        */

                        //MsfClose (pdb->msf);
                }
                else
                {
                        //PdbSetLastError (PDBERR_BAD_OR_MISSING_FILE);
                }
                
                free (pdb);
        }
        else
        {
                //PdbSetLastError (PDBERR_NO_MEMORY);
        }

        return NULL;
}






//
// Try to find & open PDB with no signature checks.
// Return Value: PPDB handle (see PdbOpenValidate for details)
//
PPDB PdbOpen (char *szPdbFileName)
{
        //return PdbOpenValidate (szPdbFileName, NULL, 0);
        return PdbOpenValidate (szPdbFileName, 0);
}






int main(int argc, char *argv[])
{
    PdbOpen(argv[1]);
}

