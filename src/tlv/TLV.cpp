/***********************************************************************/

#include "tlv/TLV.h"

/***********************************************************************/
CTLV::CTLV()
{
    m_wTag = 0;
    m_wLength = 0;
    m_pbyValue = NULL;
    m_bFirstFlag = false;
}
/********************************************************************/
CTLV::CTLV(BYTE* i_pbyBuffer)
{
    BYTE* pbyTemp;

    m_bFirstFlag = false;
    pbyTemp = BufferToTLV(i_pbyBuffer, &m_wTag, &m_wLength);
    if (pbyTemp != NULL)
    {
        m_pbyValue = new BYTE[m_wLength];
        if (m_pbyValue != NULL)
        {
            memcpy(m_pbyValue, pbyTemp, m_wLength);
            return;
        }
    }
    m_wTag = 0;
    m_wLength = 0;
    m_pbyValue = NULL;
}
/********************************************************************/
CTLV::CTLV(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue)
{
    m_wTag = 0;
    m_wLength = 0;
    m_pbyValue = NULL;
    m_bFirstFlag = false;

    if (i_pbyValue == NULL)
    {
        return;
    }

    if (i_wTag > 0xFF)
    {
        if (((HIBYTE(i_wTag) & 0x1F) != 0x1F) ||
            ((LOBYTE(i_wTag) & 0x80) == 0x80) ||
            (LOBYTE(i_wTag) == 0x00))
        {
            return;
        }
    }
    else
    {
        if ((LOBYTE(i_wTag) & 0x1F) == 0x1F)
        {
            return;
        }
    }

    m_pbyValue = new BYTE[i_wLength];
    if (m_pbyValue == NULL)
    {
        return;
    }
    m_wTag = i_wTag;
    m_wLength = i_wLength;
    memcpy(m_pbyValue, i_pbyValue, i_wLength);
}
/********************************************************************/
CTLV::~CTLV()
{
    if (m_pbyValue != NULL)
    {
        delete m_pbyValue;
        m_pbyValue = NULL;
    }
}
/********************************************************************/
void CTLV::SetTLV(BYTE* i_pbyBuffer)
{
    BYTE* pbyTemp;

    m_wTag = 0;
    m_wLength = 0;
    m_bFirstFlag = false;
    if (m_pbyValue != NULL)
    {
        delete m_pbyValue;
        m_pbyValue = NULL;
    }
    pbyTemp = BufferToTLV(i_pbyBuffer, &m_wTag, &m_wLength);
    if (pbyTemp != NULL)
    {
        m_pbyValue = new BYTE[m_wLength];
        if (m_pbyValue != NULL)
        {
            memcpy(m_pbyValue, pbyTemp, m_wLength);
            return;
        }
    }
    m_wTag = 0;
    m_wLength = 0;
    m_pbyValue = NULL;
}
/********************************************************************/
void CTLV::SetTLV(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue)
{
    m_wTag = 0;
    m_wLength = 0;
    m_bFirstFlag = false;
    if (m_pbyValue != NULL)
    {
        delete m_pbyValue;
        m_pbyValue = NULL;
    }
    if (i_pbyValue == NULL)
    {
        return;
    }
    if (i_wTag > 0xFF)
    {
        if (((HIBYTE(i_wTag) & 0x1F) != 0x1F) ||
            ((LOBYTE(i_wTag) & 0x80) == 0x80) ||
            (LOBYTE(i_wTag) == 0x00))
        {
            return;
        }
    }
    else
    {
        if ((LOBYTE(i_wTag) & 0x1F) == 0x1F)
        {
            return;
        }
    }

    m_pbyValue = new BYTE[i_wLength];
    if (m_pbyValue == NULL)
    {
        return;
    }
    m_wTag = i_wTag;
    m_wLength = i_wLength;
    memcpy(m_pbyValue, i_pbyValue, i_wLength);
}
/******************************************************************/
BYTE* CTLV::GetValue(void)
{
    return m_pbyValue;
}
/******************************************************************/
WORD CTLV::GetTag(void)
{
    return m_wTag;
}
/******************************************************************/
WORD CTLV::GetLength(void)
{
    return m_wLength;
}
/***********************************************************************/
bool CTLV::IsConstructed(WORD i_wTag)
{
    if (i_wTag > 0xFF)
    {
        return ((HIBYTE(i_wTag) & 0x20) == 0x20);
    }
    else
    {
        return ((i_wTag & 0x20) == 0x20);
    }
}
/***********************************************************************/
bool CTLV::IsConstructed(void)
{
    if (m_wTag > 0xFF)
    {
        return ((HIBYTE(m_wTag) & 0x20) == 0x20);
    }
    else
    {
        return ((m_wTag & 0x20) == 0x20);
    }
}
/***********************************************************************/
bool CTLV::IsPrimitive(WORD i_wTag)
{
    if (i_wTag > 0xFF)
    {
        return !(HIBYTE(i_wTag) & 0x20);
    }
    else
    {
        return !(i_wTag & 0x20);
    }
}
/***********************************************************************/
bool CTLV::IsPrimitive(void)
{
    if (m_wTag > 0xFF)
    {
        return !(HIBYTE(m_wTag) & 0x20);
    }
    else
    {
        return !(m_wTag & 0x20);
    }
}
/***********************************************************************/
bool CTLV::IsUniversal(void)
{
    if (m_wTag > 0xFF)
    {
        return ((!(HIBYTE(m_wTag) & 0x80)) && (!(HIBYTE(m_wTag) & 0x40)));
    }
    else
    {
        return ((!(m_wTag & 0x80)) && (!(m_wTag & 0x40)));
    }
}
/***********************************************************************/
bool CTLV::IsApplication(void)
{
    if (m_wTag > 0xFF)
    {
        return ((!(HIBYTE(m_wTag) & 0x80)) && (HIBYTE(m_wTag) & 0x40));
    }
    else
    {
        return ((!(m_wTag & 0x80)) && (m_wTag & 0x40));
    }
}
/***********************************************************************/
bool CTLV::IsContextSpecific(void)
{
    if (m_wTag > 0xFF)
    {
        return ((HIBYTE(m_wTag) & 0x80) && (!(HIBYTE(m_wTag) & 0x40)));
    }
    else
    {
        return ((m_wTag & 0x80) && (!(m_wTag & 0x40)));
    }
}
/***********************************************************************/
bool CTLV::IsPrivate(void)
{
    if (m_wTag > 0xFF)
    {
        return ((HIBYTE(m_wTag) & 0x80) && (HIBYTE(m_wTag) & 0x40));
    }
    else
    {
        return ((m_wTag & 0x80) && (m_wTag & 0x40));
    }
}
/***********************************************************************/
ULONG CTLV::TLVToBuffer(BYTE* o_pbyBuffer)
{
    ULONG ulIndex;

    if ((m_wTag == 0) || (m_wLength == 0) || (m_pbyValue == NULL))
    {
        return 0;
    }
    if (m_wTag <= 0xFF) // Tag is one byte.
    {
        o_pbyBuffer[0] = LOBYTE(m_wTag);
        ulIndex = 1;
    }
    else // Tag is two bytes.
    {
        o_pbyBuffer[0] = HIBYTE(m_wTag);
        o_pbyBuffer[1] = LOBYTE(m_wTag);
        ulIndex = 2;
    }
    if (m_wLength < 128) // Length is one byte.
    {
        o_pbyBuffer[ulIndex] = LOBYTE(m_wLength);
        ulIndex += 1;
    }
    else if (m_wLength <= 0xFF) // Length is two bytes.
    {
        o_pbyBuffer[ulIndex] = 0x81;
        o_pbyBuffer[ulIndex + 1] = LOBYTE(m_wLength);
        ulIndex += 2;
    }
    else // Length is three bytes.
    {
        o_pbyBuffer[ulIndex] = 0x82;
        o_pbyBuffer[ulIndex + 1] = HIBYTE(m_wLength);
        o_pbyBuffer[ulIndex + 2] = LOBYTE(m_wLength);
        ulIndex += 3;
    }
    memcpy(o_pbyBuffer + ulIndex, m_pbyValue, m_wLength);

    return ulIndex + m_wLength;
}
/***********************************************************************/
BYTE* CTLV::BufferToTLV(BYTE* i_pbyBuffer, WORD* o_pwTag, WORD* o_pwLength)
{
    BYTE byIndex;

    if (i_pbyBuffer == NULL)
    {
        return NULL;
    }
    if (i_pbyBuffer[0] == 0x00)
    {
        return NULL;
    }
    if ((i_pbyBuffer[0] & 0x1F) == 0x1F) // Tag is two bytes.
    {
        if ((i_pbyBuffer[1] & 0x80) == 0x80)
        {
            return NULL;
        }
        (*o_pwTag) = (i_pbyBuffer[0] * 256) + i_pbyBuffer[1];
        byIndex = 2;
    }
    else // Tag is one byte.
    {
        (*o_pwTag) = i_pbyBuffer[0];
        byIndex = 1;
    }

    if (i_pbyBuffer[byIndex] == 0x00)
    {
        return NULL;
    }
    if (i_pbyBuffer[byIndex] <= 127) // Length is one byte.
    {
        (*o_pwLength) = i_pbyBuffer[byIndex];
        return i_pbyBuffer + byIndex + 1;
    }
    switch (i_pbyBuffer[byIndex])
    {
        case 0x81: // Length is two bytes.
            (*o_pwLength) = i_pbyBuffer[byIndex + 1];
            return i_pbyBuffer + byIndex + 2;
            break;

        case 0x82: // Length is three bytes.
            (*o_pwLength) = (i_pbyBuffer[byIndex + 1] * 256) + i_pbyBuffer[byIndex + 2];
            return i_pbyBuffer + byIndex + 3;
            break;

        default:
            return NULL;
            break;
    }
}
/***********************************************************************/
bool CTLV::IsBERTLV(void)
{
    return ((m_wTag != 0) && (m_wLength != 0) && (m_pbyValue != NULL));
}
/***********************************************************************/
bool CTLV::GetFirstSubTLV(CTLV* o_ptlvSubTLV)
{
    BYTE* pbyTemp;
    WORD wTag;
    WORD wLength;

    m_bFirstFlag = false;
    if ((!IsBERTLV()) || (IsPrimitive()))
    {
        return false;
    }
    pbyTemp = BufferToTLV(m_pbyValue, &wTag, &wLength);
    if (pbyTemp != NULL)
    {
        o_ptlvSubTLV->SetTLV(wTag, wLength, pbyTemp);
        if (o_ptlvSubTLV->IsBERTLV())
        {
            m_bFirstFlag = true;
            m_pbySubTLVIndex = pbyTemp + wLength;
            return true;
        }
    }

    return false;
}
/***********************************************************************/
bool CTLV::GetNextSubTLV(CTLV* o_ptlvSubTLV)
{
    BYTE* pbyTemp;
    WORD wTag;
    WORD wLength;

    if (!m_bFirstFlag)
    {
        return false;
    }
    m_bFirstFlag = false;
    if ((!IsBERTLV()) || (IsPrimitive()))
    {
        return false;
    }
    if (m_pbySubTLVIndex >= m_pbyValue + m_wLength)
    {
        return false;
    }
    pbyTemp = BufferToTLV(m_pbySubTLVIndex, &wTag, &wLength);
    if (pbyTemp != NULL)
    {
        o_ptlvSubTLV->SetTLV(wTag, wLength, pbyTemp);
        if (o_ptlvSubTLV->IsBERTLV())
        {
            m_bFirstFlag = true;
            m_pbySubTLVIndex = pbyTemp + wLength;
            return true;
        }
    }

    return false;
}
/***********************************************************************/
bool CTLV::GetSubTLV(WORD i_wTag, CTLV* o_ptlvSubTLV)
{
    CTLV tlvTemp;

    if (!GetFirstSubTLV(&tlvTemp))
    {
        return false;
    }
    if (tlvTemp.GetTag() == i_wTag)
    {
        (*o_ptlvSubTLV) = tlvTemp;
        return true;
    }
    while (GetNextSubTLV(&tlvTemp))
    {
        if (tlvTemp.GetTag() == i_wTag)
        {
            (*o_ptlvSubTLV) = tlvTemp;
            return true;
        }
    }

    return false;
}
/***********************************************************************/
