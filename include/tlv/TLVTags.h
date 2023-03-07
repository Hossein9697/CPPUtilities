#ifndef __TLV_TAGS_H
#define __TLV_TAGS_H

// #include "TLV.h"
// #include "TLVList.h"
// #include "SysExp.h"
//
// #pragma pack(1)

// TLV TAGs
//////////////////////////////////////////////////////////////////////////////////////////

namespace Tlv
{
enum
{
    AdditionalDataTag = 0x0075
};
namespace AdditionalData
{
enum
{
    ParameterTag = 0x00B0,
    ReferenceToFileTag = 0x00A5
};
namespace Parameter
{
enum
{
    NameTag = 0x0081,
    ValueTag = 0x0082,
    IndexTag = 0x0083,
    TLVValueTag = 0x0084,
    NullValueTag = 0x0086,
    ContainerTag = 0x00A0
};
}
namespace ReferenceToFile
{
enum
{
    ApplicationFileTag = 0x00B0
};
namespace ApplicationFile
{
enum
{
    FileNameTag = 0x0080,
    ApplicationTypeTag = 0x0081,
    RegistrationTypeTag = 0x0082,
    RegistrationOnAgentTag = 0x0083,
    ApplicationIDTag = 0x0084
};
}
} // namespace ReferenceToFile
} // namespace AdditionalData
} // namespace Tlv

#endif
