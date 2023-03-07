/******************************************************************************/
/*                                                                            */
/* Copyright (C) 2005-2007 Oscar Sanderson                                    */
/*                                                                            */
/* This software is provided 'as-is', without any express or implied          */
/* warranty.  In no event will the author(s) be held liable for any damages   */
/* arising from the use of this software.                                     */
/*                                                                            */
/* Permission is granted to anyone to use this software for any purpose,      */
/* including commercial applications, and to alter it and redistribute it     */
/* freely, subject to the following restrictions:                             */
/*                                                                            */
/* 1. The origin of this software must not be misrepresented; you must not    */
/*    claim that you wrote the original software. If you use this software    */
/*    in a product, an acknowledgment in the product documentation would be   */
/*    appreciated but is not required.                                        */
/*                                                                            */
/* 2. Altered source versions must be plainly marked as such, and must not be */
/*    misrepresented as being the original software.                          */
/*                                                                            */
/* 3. This notice may not be removed or altered from any source distribution. */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* String manipulation module                                                 */
/*                                                                            */
/******************************************************************************/

#include "iso8583/include/dl_str.h"
#include <ctype.h>
/******************************************************************************/

DL_CHAR kDL_STR_EmptyStr[1] = {kDL_ASCII_NULL};

/******************************************************************************/

DL_CHAR *DL_STR_GetEnv ( const DL_CHAR *iEnvStr )
{
    return DL_STR_SafeStr((DL_CHAR*)getenv((const char*)iEnvStr));
}

/******************************************************************************/

DL_UINT32 DL_STR_StrLen ( const DL_CHAR *iStr )
{
    DL_UINT32 len = 0;

    if ( iStr != NULL )
        len = (DL_UINT32)strlen((const char*)iStr);

	return len;
}

/******************************************************************************/

int DL_STR_StrLenExWS ( const DL_CHAR *iStr )
{
    int len = 0;

    iStr = DL_STR_SafeStr(iStr);

    while ( *iStr != kDL_ASCII_NULL )
    {
		if ( !DL_STR_IsWS(*iStr) )
			len++;
        
        iStr++;
    }
    
    return len;
}

/******************************************************************************/

int DL_STR_StrCmp ( DL_CHAR *iStr1,
                    DL_CHAR *iStr2,
				    int            iIgnoreCase )
{
	return DL_STR_StrNCmp(iStr1,iStr2,iIgnoreCase,
                          MAX((int)DL_STR_StrLen(iStr1),(int)DL_STR_StrLen(iStr2)));
}

/******************************************************************************/

int DL_STR_StrNCmp ( DL_CHAR *iStr1,
                     DL_CHAR *iStr2,
				     int            iIgnoreCase,
				     int            iMaxChars )
{
	int retVal = 0;
	int ch1,ch2;
	int charCnt = 0;

	/* ensure we don't have any NULL pointers */
    iStr1 = DL_STR_SafeStr((DL_CHAR*)iStr1);
    iStr2 = DL_STR_SafeStr((DL_CHAR*)iStr2);

	while ( charCnt <= iMaxChars )
	{
		if ( !(*iStr1) && !(*iStr2) )
		{
			/* reached end of both strings */
			retVal = 0;
			break;
		}
		else if ( !(*iStr1) )
		{
			/* reached end of str1 */
			retVal = -1;
			break;
		}
		else if ( !(*iStr2) )
		{
			/* reach end of str2 */
			retVal = 1;
			break;
		}
		else /* perform character level compare */
		{
			/* get current characters */
			if ( iIgnoreCase )
			{
				ch1 = toupper((int)*iStr1);
				ch2 = toupper((int)*iStr2);
			}
			else
			{
				ch1 = (int)*iStr1;
				ch2 = (int)*iStr2;
			}

			if ( ch1 < ch2 )
			{
				retVal = -1;
				break;
			}
			else if ( ch1 > ch2 )
			{
				retVal = 1;
				break;
			}
		}

		iStr1++;
		iStr2++;
		charCnt++;
	} /* end-while */

	return retVal;
}

/******************************************************************************/

void DL_STR_StrCpy ( DL_CHAR       *ioToPtr,
				     const DL_CHAR *iFromPtr,
                     DL_UINT32            iMaxChars )
{
	if ( iFromPtr == NULL ) /* have NULL */
	{
		ioToPtr[0] = kDL_ASCII_NULL;
	}
	else if ( DL_STR_StrLen(iFromPtr) <= iMaxChars ) /* within length */
	{
		/* simple string copy */
        (void)strcpy((char*)ioToPtr,(const char*)iFromPtr);
	}
	else /* too long - so chop */
	{
		/* chop - add null */
		DL_MEM_memcpy(ioToPtr,iFromPtr,iMaxChars);
		ioToPtr[iMaxChars] = kDL_ASCII_NULL;
	}

	return;
}

/******************************************************************************/

DL_ERR DL_STR_StrDup ( const DL_CHAR  *iStr,
					   DL_CHAR       **oStr )
{
	return DL_STR_StrNDup(iStr,DL_STR_StrLen(iStr),oStr);
}

/******************************************************************************/

DL_ERR DL_STR_StrNDup ( const DL_CHAR  *iStr,
					    DL_UINT32       iMaxChars,
						DL_CHAR       **oStr )
{
	DL_ERR err = kDL_ERR_NONE;

	/* init outputs */
	*oStr = NULL;

	if ( NULL == iStr )
	{
		err = kDL_ERR_OTHER;
	}
    else if ( DL_MEM_malloc(iMaxChars+1,(void**)oStr) )
	{
		/* error - do nothing */
        err = DL_MEM_malloc(iMaxChars+1,(void**)oStr);
	}
	else
	{
        DL_STR_StrCpy(*oStr,iStr,iMaxChars);
	}

	return err;
}

/******************************************************************************/

DL_ERR DL_STR_StrCat ( const DL_CHAR  *iStr1,
					   const DL_CHAR  *iStr2,
					   DL_CHAR       **oStr )
{
	DL_ERR err     = kDL_ERR_NONE;
    DL_UINT32    str1len = 0;
    DL_UINT32    str2len = 0;

	/* init outputs */
	*oStr = NULL;

	/* ensure inputs are valid */
	iStr1 = DL_STR_SafeStr(iStr1);
	iStr2 = DL_STR_SafeStr(iStr2);

	/* determine string lengths */
	str1len = DL_STR_StrLen(iStr1);
	str2len = DL_STR_StrLen(iStr2);

	/* allocate memory for combined string */
    err = DL_MEM_malloc(str1len+str2len+1,(void**)oStr);

	if ( !err )
	{
		DL_MEM_memcpy(oStr        ,iStr1,str1len);
		DL_MEM_memcpy(oStr+str1len,iStr2,str2len);
		oStr[str1len+str2len] = kDL_ASCII_NULL;
	}

	return err;
}

/******************************************************************************/

void DL_STR_LTrim ( DL_CHAR *ioStr,
				    DL_CHAR  iTrimCh )
{
	DL_CHAR *ptr = NULL;

	/* ensure 'str' is not null */
	ioStr = DL_STR_SafeStr(ioStr);

	/* get pointer to start of string */
	ptr = ioStr;

	/* move past leading trim characters */
	while ( *ptr == iTrimCh )
		ptr++;

	/* shift characters back */
	if ( ptr > ioStr )
	{
		DL_CHAR *ptr2 = ioStr;

		while ( *ptr != kDL_ASCII_NULL )
			*ptr2++ = *ptr++;

		/* null terminate */
		*ptr2 = kDL_ASCII_NULL;
	}

	return;
}

/******************************************************************************/

void DL_STR_RTrim ( DL_CHAR *ioStr,
					DL_CHAR  iTrimCh )
{
	DL_CHAR *ptr = NULL;

	/* ensure 'str' is not null */
	ioStr = DL_STR_SafeStr(ioStr);

	/* get pointer to end of string */
	ptr = ioStr + DL_STR_StrLen(ioStr);

	while ( ptr > ioStr )
	{
		--ptr;

		if ( *ptr == iTrimCh )
			*ptr = kDL_ASCII_NULL;
		else
			break;
	}

	return;
}

/******************************************************************************/

void DL_STR_ToUpper ( DL_CHAR *ioStr )
{
	if ( ioStr != NULL )
	{
		while ( *ioStr++ != kDL_ASCII_NULL )
		{
			*ioStr = (DL_CHAR)toupper((int)*ioStr);
		}
	}

	return;
}

/******************************************************************************/

DL_CHAR *DL_STR_SkipWS ( DL_CHAR *iStr )
{
    while ( DL_STR_IsWS(*iStr) )
        iStr++;

    return iStr;
}

/******************************************************************************/

int DL_STR_IsNumeric ( const DL_CHAR *iStr )
{
	int ok = 0; /* assume NO */

	if ( iStr != NULL )
	{
		ok = 1;

		while ( (*iStr != kDL_ASCII_NULL) && ok )
		{
			if ( !((*iStr >= '0') && (*iStr <= '9')) )
				ok = 0;

			iStr++; /* moved here to satisfy lint */
		} /* end-while */
	} /* end-if */

	return ok;
}

/******************************************************************************/

int DL_STR_Validate ( const DL_CHAR *iStr,
					  int            iMinLen,
				      int            iMaxLen,
					  const DL_CHAR *iValidChars )
{
	int ok = 0; /* default to invalid */
	int i;

	if ( iStr != NULL )
	{
		ok = 1;

		/* check minimum length */
		if ( (iMinLen != -1) && ((int)DL_STR_StrLen(iStr) < iMinLen) )
			ok = 0;

		/* check maximum length */
		if ( ok && (iMaxLen != -1) && ((int)DL_STR_StrLen(iStr) > iMaxLen) )
			ok = 0;

		if ( ok && (iValidChars != NULL) )
		{
			/* validate contents */
			for ( i=0 ; (i<(int)DL_STR_StrLen(iStr)) && ok ; i++ )
                if ( DL_STR_StrChr((const char*)iValidChars,(int)(iStr[i])) == NULL )
					ok = 0;
		}
	}

	return ok;
}

/******************************************************************************/

int DL_STR_Contains ( const DL_CHAR *iStr,
					  const DL_CHAR *iContains )
{
	int ret = 0; /* assume No */

	if ( (iStr != NULL) && (iContains != NULL) )
	{
		while ( *iStr != kDL_ASCII_NULL )
		{
            if ( DL_STR_StrChr((const char*)iContains,(int)(*iStr)) != NULL )
			{
				ret = 1;
				break;
			}

			iStr++;
		} /* end-while */
	}

	return ret;
}

/******************************************************************************/


