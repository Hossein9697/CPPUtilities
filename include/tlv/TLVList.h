/***********************************************************************/
#ifndef __TLV_LIST_H__
#define __TLV_LIST_H__
/***********************************************************************/

#include "NTLV.h"

class CTLVList
{
private:
    CNTLV* m_pntlvHead;
    CNTLV* m_pntlvNextTLV;
    bool m_bFirstFlag;

public:
    CTLVList();
    virtual ~CTLVList();

    void Add(CTLV* i_ptlvNewTLV);
    void Add(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue);
    void Add(BYTE* i_pbyBuffer);

    bool Update(CTLV* i_ptlvNewTLV);
    bool Update(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue);

    void Delete(CTLV* i_ptlvOldTLV);
    void Delete(WORD i_wTag);

    void Empty(void);
    bool IsEmpty(void);

    bool GetFirstTLV(CTLV* o_ptlvFirst);
    bool GetNextTLV(CTLV* o_ptlvNext);
    bool GetTLV(WORD i_wTag, CTLV* o_ptlvTemp);

    bool IsMember(CTLV* i_ptlvUnKnown);
    bool IsMember(WORD i_wTag, WORD i_wLength, BYTE* i_pbyValue);

    bool GenerateConstructedTLV(WORD i_wTag, CTLV* o_ptlvAllTLV);

    void GetDataXDOL(CTLV* i_ptlvXDOL, WORD i_wDataTag, CTLV* o_ptlvData);
    static bool SearchTagXDOL(WORD i_wTag, CTLV* i_ptlvXDOL);

    const CTLVList& operator=(CTLVList& i_ptlvlstTemp)
    {
        CTLV tlvTemp;
        CTLVList tlvlstTemp;
        m_bFirstFlag = false;
        Empty();
        tlvlstTemp.Empty();
        if (i_ptlvlstTemp.GetFirstTLV(&tlvTemp))
        {
            do
            {
                tlvlstTemp.Add(&tlvTemp);
            } while (i_ptlvlstTemp.GetNextTLV(&tlvTemp));
        }
        if (tlvlstTemp.GetFirstTLV(&tlvTemp))
        {
            do
            {
                Add(&tlvTemp);
            } while (tlvlstTemp.GetNextTLV(&tlvTemp));
        }

        return *this;
    };
};

/***********************************************************************/
#endif // for __TLV_LIST_H__
/***********************************************************************/
