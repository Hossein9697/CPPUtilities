/***********************************************************************/

#include "tlv/TLVList.h"

/***********************************************************************/
CTLVList::CTLVList()
{
    m_pntlvHead = NULL;
    m_pntlvNextTLV = NULL;
    m_bFirstFlag = false;
}
/***********************************************************************/
CTLVList::~CTLVList()
{
    Empty();
}
/***********************************************************************/
void CTLVList::Add(CTLV* i_ptlvNewTLV)
{
    CNTLV* pntlvTemp;

    m_bFirstFlag = false;
    pntlvTemp = new CNTLV;
    if (pntlvTemp == NULL)
    {
        return;
    }
    pntlvTemp->m_tlvValue = (*i_ptlvNewTLV);
    if (!pntlvTemp->m_tlvValue.IsBERTLV())
    {
        delete pntlvTemp;
        return;
    }
    pntlvTemp->m_pntlvNext = m_pntlvHead;
    m_pntlvHead = pntlvTemp;
}
/***********************************************************************/
void CTLVList::Add(BYTE* i_pbyBuffer)
{
    CNTLV* pntlvTemp;

    m_bFirstFlag = false;
    pntlvTemp = new CNTLV;
    if (pntlvTemp == NULL)
    {
        return;
    }
    pntlvTemp->m_tlvValue.SetTLV(i_pbyBuffer);
    if (!pntlvTemp->m_tlvValue.IsBERTLV())
    {
        delete pntlvTemp;
        return;
    }
    pntlvTemp->m_pntlvNext = m_pntlvHead;
    m_pntlvHead = pntlvTemp;
}
/***********************************************************************/
void CTLVList::Add(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue)
{
    CNTLV* pntlvTemp;

    m_bFirstFlag = false;
    pntlvTemp = new CNTLV;
    if (pntlvTemp == NULL)
    {
        return;
    }
    pntlvTemp->m_tlvValue.SetTLV(i_wTag, i_wLength, i_pbyValue);
    if (!pntlvTemp->m_tlvValue.IsBERTLV())
    {
        delete pntlvTemp;
        return;
    }
    pntlvTemp->m_pntlvNext = m_pntlvHead;
    m_pntlvHead = pntlvTemp;
}
/***********************************************************************/
bool CTLVList::GetFirstTLV(CTLV* o_ptlvFirst)
{
    m_bFirstFlag = false;
    if (m_pntlvHead == NULL)
    {
        return false;
    }
    (*o_ptlvFirst) = m_pntlvHead->m_tlvValue;
    m_pntlvNextTLV = m_pntlvHead->m_pntlvNext;
    m_bFirstFlag = true;

    return true;
}
/***********************************************************************/
bool CTLVList::GetNextTLV(CTLV* o_ptlvNext)
{
    if (!m_bFirstFlag)
    {
        return false;
    }
    if (m_pntlvNextTLV == NULL)
    {
        return false;
    }
    (*o_ptlvNext) = m_pntlvNextTLV->m_tlvValue;
    m_pntlvNextTLV = m_pntlvNextTLV->m_pntlvNext;

    return true;
}
/***********************************************************************/
bool CTLVList::GetTLV(WORD i_wTag, CTLV* o_ptlvTemp)
{
    CTLV tlvTemp;

    if (!GetFirstTLV(&tlvTemp))
    {
        return false;
    }
    if (tlvTemp.GetTag() == i_wTag)
    {
        (*o_ptlvTemp) = tlvTemp;
        return true;
    }
    while (GetNextTLV(&tlvTemp))
    {
        if (tlvTemp.GetTag() == i_wTag)
        {
            (*o_ptlvTemp) = tlvTemp;
            return true;
        }
    }

    return false;
}
/***********************************************************************/
bool CTLVList::Update(CTLV* i_ptlvNewTLV)
{
    CNTLV* pntlvTemp;

    m_bFirstFlag = false;
    pntlvTemp = m_pntlvHead;
    while (pntlvTemp != NULL)
    {
        if (pntlvTemp->m_tlvValue.GetTag() == i_ptlvNewTLV->GetTag())
        {
            pntlvTemp->m_tlvValue.SetTLV(i_ptlvNewTLV->GetTag(), i_ptlvNewTLV->GetLength(), i_ptlvNewTLV->GetValue());
            return true;
        }
        pntlvTemp = pntlvTemp->m_pntlvNext;
    }
    Add(i_ptlvNewTLV);

    return false;
}
/***********************************************************************/
bool CTLVList::Update(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue)
{
    CNTLV* pntlvTemp;

    m_bFirstFlag = false;
    pntlvTemp = m_pntlvHead;
    while (pntlvTemp != NULL)
    {
        if (pntlvTemp->m_tlvValue.GetTag() == i_wTag)
        {
            pntlvTemp->m_tlvValue.SetTLV(i_wTag, i_wLength, i_pbyValue);
            return true;
        }
        pntlvTemp = pntlvTemp->m_pntlvNext;
    }
    Add(i_wTag, i_wLength, i_pbyValue);

    return false;
}
/***********************************************************************/
void CTLVList::Empty(void)
{
    CNTLV* pntlvTemp;

    m_bFirstFlag = false;
    while (m_pntlvHead != NULL)
    {
        pntlvTemp = m_pntlvHead;
        m_pntlvHead = m_pntlvHead->m_pntlvNext;
        delete pntlvTemp;
    }
}
/************************************************************************/
bool CTLVList::IsEmpty(void)
{
    if (m_pntlvHead == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/***********************************************************************/
void CTLVList::Delete(CTLV* i_ptlvOldTLV)
{
    CNTLV *pntlvPrevious, *pntlvCurrent;

    m_bFirstFlag = false;
    if (m_pntlvHead == NULL)
    {
        return;
    }
    if (m_pntlvHead->m_tlvValue == (*i_ptlvOldTLV))
    {
        pntlvCurrent = m_pntlvHead;
        m_pntlvHead = m_pntlvHead->m_pntlvNext;
        delete pntlvCurrent;
        return;
    }
    pntlvPrevious = m_pntlvHead;
    pntlvCurrent = m_pntlvHead->m_pntlvNext;
    while (pntlvCurrent != NULL)
    {
        if (pntlvCurrent->m_tlvValue == (*i_ptlvOldTLV))
        {
            pntlvPrevious->m_pntlvNext = pntlvCurrent->m_pntlvNext;
            delete pntlvCurrent;
            return;
        }
        pntlvPrevious = pntlvCurrent;
        pntlvCurrent = pntlvCurrent->m_pntlvNext;
    }
}
/***********************************************************************/
void CTLVList::Delete(WORD i_wTag)
{
    CNTLV *pntlvPrevious, *pntlvCurrent;

    m_bFirstFlag = false;
    if (m_pntlvHead == NULL)
    {
        return;
    }
    if (m_pntlvHead->m_tlvValue.GetTag() == i_wTag)
    {
        pntlvCurrent = m_pntlvHead;
        m_pntlvHead = m_pntlvHead->m_pntlvNext;
        delete pntlvCurrent;
        return;
    }
    pntlvPrevious = m_pntlvHead;
    pntlvCurrent = m_pntlvHead->m_pntlvNext;
    while (pntlvCurrent != NULL)
    {
        if (pntlvCurrent->m_tlvValue.GetTag() == i_wTag)
        {
            pntlvPrevious->m_pntlvNext = pntlvCurrent->m_pntlvNext;
            delete pntlvCurrent;
            return;
        }
        pntlvPrevious = pntlvCurrent;
        pntlvCurrent = pntlvCurrent->m_pntlvNext;
    }
}
/***********************************************************************/
bool CTLVList::IsMember(CTLV* i_ptlvUnKnown)
{
    CNTLV* pntlvTemp;

    m_bFirstFlag = false;
    pntlvTemp = m_pntlvHead;
    while (pntlvTemp != NULL)
    {
        if (pntlvTemp->m_tlvValue.GetTag() == i_ptlvUnKnown->GetTag() &&
            pntlvTemp->m_tlvValue.GetLength() == i_ptlvUnKnown->GetLength() &&
            !memcmp(pntlvTemp->m_tlvValue.GetValue(), i_ptlvUnKnown->GetValue(), i_ptlvUnKnown->GetLength()))
        {
            return true;
        }
        pntlvTemp = pntlvTemp->m_pntlvNext;
    }
    return false;
}
/***********************************************************************/
bool CTLVList::IsMember(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue)
{
    CNTLV* pntlvTemp;

    m_bFirstFlag = false;
    pntlvTemp = m_pntlvHead;
    while (pntlvTemp != NULL)
    {
        if (pntlvTemp->m_tlvValue.GetTag() == i_wTag &&
            pntlvTemp->m_tlvValue.GetLength() == i_wLength &&
            !memcmp(pntlvTemp->m_tlvValue.GetValue(), i_pbyValue, i_wLength))
        {
            return true;
        }
        pntlvTemp = pntlvTemp->m_pntlvNext;
    }
    return false;
}
/***********************************************************************/
bool CTLVList::SearchTagXDOL(WORD i_wTag, CTLV* i_ptlvXDOL)
{
    BYTE* pbyIndex;
    WORD wTempTag;
    WORD wTempLength;
    BYTE* pbyXDOL;
    WORD wXDOLLen;

    pbyIndex = pbyXDOL = i_ptlvXDOL->GetValue();
    wXDOLLen = i_ptlvXDOL->GetLength();
    while ((pbyIndex <= pbyXDOL + wXDOLLen) && (pbyIndex != NULL))
    {
        pbyIndex = CTLV::BufferToTLV(pbyIndex, &wTempTag, &wTempLength);
        if (wTempTag == i_wTag)
        {
            return true;
        }
    }

    return false;
}
/***********************************************************************/
void CTLVList::GetDataXDOL(CTLV* i_ptlvXDOL, WORD i_wDataTag, CTLV* o_ptlvData)
{
    BYTE byaData[0xFFFF];
    BYTE* pbyIndex;
    WORD wXDataLength = 0;
    WORD wTempTag;
    WORD wTempLength;
    BYTE* pbyXDOL;
    WORD wXDOLLen;
    CTLV tlvTemp;
    BYTE byaZero[0xFFFF];

    // SecureZeroMemory( byaZero , 0xFFFF );
    memset(byaZero, 0xFF, 0xFFFF);

    pbyIndex = pbyXDOL = i_ptlvXDOL->GetValue();
    wXDOLLen = i_ptlvXDOL->GetLength();
    while ((pbyIndex < pbyXDOL + wXDOLLen) && (pbyIndex != NULL))
    {
        pbyIndex = CTLV::BufferToTLV(pbyIndex, &wTempTag, &wTempLength);
        if ((!GetTLV(wTempTag, &tlvTemp)) ||
            (CTLV::IsConstructed(wTempTag)))
        {
            tlvTemp.SetTLV(wTempTag, wTempLength, byaZero);
        }
        memcpy(byaData + wXDataLength, tlvTemp.GetValue(), wTempLength);
        wXDataLength += wTempLength;
    }
    o_ptlvData->SetTLV(i_wDataTag, wXDataLength, byaData);
}
/***********************************************************************/
bool CTLVList::GenerateConstructedTLV(WORD i_wTag, CTLV* o_ptlvAllTLV)
{
    CTLV tlvTemp;
    WORD wIndex = 0;
    BYTE byaBuffer[0xFFFF];

    if (GetFirstTLV(&tlvTemp) == false)
    {
        return false;
    }
    do
    {
        wIndex += (WORD)tlvTemp.TLVToBuffer(byaBuffer + wIndex);
    } while (GetNextTLV(&tlvTemp));
    tlvTemp.SetTLV(i_wTag, wIndex, byaBuffer);
    if ((tlvTemp.IsBERTLV() == false) || (tlvTemp.IsConstructed() == false))
    {
        return false;
    }
    o_ptlvAllTLV->SetTLV(i_wTag, wIndex, byaBuffer);

    return true;
}
/***********************************************************************/
