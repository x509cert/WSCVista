// dynamicbase.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifndef IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE
#define		IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE  0x0040
#endif

bool FCheckImage(FILE *fd)
{
   IMAGE_DOS_HEADER DosHeader;
   if (fread(&DosHeader, sizeof(DosHeader), 1, fd) != 1)
      return(false);

   if (DosHeader.e_magic != IMAGE_DOS_SIGNATURE)
   {
      // The file isn't an MS-DOS executable
      return(false);
   }

   if (DosHeader.e_lfanew == 0)
   {
      // There is no pointer to a PE header
      return(false);
   }

   if (fseek(fd, DosHeader.e_lfanew, SEEK_SET) != 0)
   {
      // The file isn't large enough to contain a PE header
      return(false);
   }

   // Read the PE header.
   IMAGE_NT_HEADERS32 NtHeader32;
   if (fread(&NtHeader32, sizeof(NtHeader32), 1, fd) != 1)
   {
      // The file isn't large enough to contain a PE header
      return(false);
   }

   if (NtHeader32.Signature != IMAGE_NT_SIGNATURE)
   {
      // The file isn't a PE executable
      return(false);
   }

   if (NtHeader32.OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
   {
      if ((NtHeader32.OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE) != 0)
      {
		// Image is marked as using dynamicbase
		return(true);
      }
   }

   else if (NtHeader32.OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
   {
      // The DllCharacteristics field is within the range of the size of the 32 bit headers
      IMAGE_NT_HEADERS64 *pNtHeader64 = (IMAGE_NT_HEADERS64 *) &NtHeader32;
      if ((pNtHeader64->OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE) != 0)
      {
		// Image is marked as using dynamicbase
		return(true);
      }
   }
   else
   {
      printf("Invalid executable\n");
      return(false);
   }

   if (fseek(fd, DosHeader.e_lfanew + offsetof(IMAGE_NT_HEADERS, OptionalHeader) + NtHeader32.FileHeader.SizeOfOptionalHeader, SEEK_SET) == 0)
   {
      size_t cish = NtHeader32.FileHeader.NumberOfSections;
      IMAGE_SECTION_HEADER *rgish = new IMAGE_SECTION_HEADER[cish];
      if (fread(rgish, sizeof(IMAGE_SECTION_HEADER), cish, fd) != cish)
      {
		 delete [] rgish;
		 return(false);
      }
      delete [] rgish;
   }
   return(false);
}


int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2) {
		wprintf(L"Usage: dynamicase <filename>");
		return -1;
	}

	FILE *f = NULL;
	if ((_wfopen_s(&f,argv[1],L"r") != 0) || f == NULL) {
		wprintf(L"Unable to open %s",argv[1]);
		return -2;
	}

	wprintf(L"%s with /DYNAMICBASE", FCheckImage(f) ? L"Linked" : L"NOT linked");

	fclose(f);
	return 0;
}
