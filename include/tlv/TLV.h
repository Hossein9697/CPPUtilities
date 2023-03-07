/***********************************************************************/
#ifndef __TLV_H__
#define __TLV_H__
/***********************************************************************/
#include <cstring>
#include "Types.h"

class CTLV
{
private:
    WORD m_wTag;
    WORD m_wLength;
    BYTE* m_pbyValue;

    bool m_bFirstFlag;
    BYTE* m_pbySubTLVIndex;

public:
    CTLV();
    CTLV(const CTLV& i_ptlvTemp)
    {
        m_bFirstFlag = false;
        // 		if( m_pbyValue != NULL )
        // 		{
        // 			delete m_pbyValue;
        // 			m_pbyValue = NULL;
        // 		}
        m_pbyValue = new BYTE[i_ptlvTemp.m_wLength];
        if (m_pbyValue != NULL)
        {
            memcpy(m_pbyValue, i_ptlvTemp.m_pbyValue, i_ptlvTemp.m_wLength);
            m_wTag = i_ptlvTemp.m_wTag;
            m_wLength = i_ptlvTemp.m_wLength;
        }
        else
        {
            m_wTag = 0;
            m_wLength = 0;
        }
    }
    CTLV(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue);
    CTLV(BYTE* i_pbyBuffer);
    virtual ~CTLV();

    void SetTLV(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue);
    void SetTLV(BYTE* i_pbyBuffer);

    WORD GetLength(void);
    WORD GetTag(void);
    BYTE* GetValue(void);

    static bool IsConstructed(WORD i_wTag);
    static bool IsPrimitive(WORD i_wTag);
    bool IsConstructed(void);
    bool IsPrimitive(void);

    bool IsUniversal(void);
    bool IsApplication(void);
    bool IsContextSpecific(void);
    bool IsPrivate(void);

    bool IsBERTLV(void);

    bool GetFirstSubTLV(CTLV* o_ptlvSubTLV);
    bool GetNextSubTLV(CTLV* o_ptlvSubTLV);
    bool GetSubTLV(WORD i_wTag, CTLV* o_ptlvSubTLV);

    ULONG TLVToBuffer(BYTE* o_pbyBuffer);
    static BYTE* BufferToTLV(BYTE* i_pbyBuffer, WORD* o_pwTag, WORD* o_pwLength);

    bool operator==(const CTLV& i_ptlvTemp)
    {
        if ((m_wTag == i_ptlvTemp.m_wTag) &&
            (m_wLength == i_ptlvTemp.m_wLength) &&
            (memcmp(m_pbyValue, i_ptlvTemp.m_pbyValue, m_wLength) == 0))
        {
            return true;
        }
        return false;
    };

    bool operator!=(const CTLV& i_ptlvTemp)
    {
        if ((m_wTag != i_ptlvTemp.m_wTag) ||
            (m_wLength != i_ptlvTemp.m_wLength) ||
            (memcmp(m_pbyValue, i_ptlvTemp.m_pbyValue, m_wLength) != 0))
        {
            return true;
        }
        return false;
    };

    const CTLV& operator=(CTLV& i_ptlvTemp)
    {
        m_bFirstFlag = false;
        if (m_pbyValue != NULL)
        {
            delete m_pbyValue;
            m_pbyValue = NULL;
        }
        m_pbyValue = new BYTE[i_ptlvTemp.m_wLength];
        if (m_pbyValue != NULL)
        {
            memcpy(m_pbyValue, i_ptlvTemp.m_pbyValue, i_ptlvTemp.m_wLength);
            m_wTag = i_ptlvTemp.m_wTag;
            m_wLength = i_ptlvTemp.m_wLength;
        }
        else
        {
            m_wTag = 0;
            m_wLength = 0;
        }

        return *this;
    };
};

/***********************************************************************/
#endif // for __TLV_H__
/***********************************************************************/
