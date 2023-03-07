#include "wosa/error-names/WosaErrorNamesUtility.hpp"
#include "wosa/error-names/WosaDeviceHeaders.hpp"
#include "wosa/error-names/DeviceDefinition.hpp"

std::string WosaErrorNamesUtility::getHResultDescription(DeviceType deviceType, HRESULT errorCode)
{
    if (errorCode < 0 && errorCode > -100)
        return getGeneralErrorDescription(errorCode);

    switch (deviceType)
    {
        case DeviceType::BarcodeReader:
            return getBarcodeReaderErrorDescription(errorCode);
        case DeviceType::CameraDevice:
            return getCameraDeviceErrorDescription(errorCode);
        case DeviceType::CashDispenserModule:
            return getCashDispenserErrorDescription(errorCode);
        case DeviceType::CashInModule:
            return getCashInModuleErrorDescription(errorCode);
        case DeviceType::Depository:
            return getDepositoryErrorDescription(errorCode);
        case DeviceType::IdentificationCard:
            return getIdentificationCardErrorDescription(errorCode);
        case DeviceType::JournalPrinter:
        case DeviceType::PassbookPrinter:
        case DeviceType::ReceiptPrinter:
        case DeviceType::StatementPrinter:
        case DeviceType::Printer:
            return getPrinterErrorDescription(errorCode);
        case DeviceType::PINKeypad:
            return getPINKeypadDescription(errorCode);
        case DeviceType::SensorsAndIndicatorsUnit:
            return getSensorsAndIndicatorsUnitErrorDescription(errorCode);
        case DeviceType::TextTerminalUnit:
            return getTextTerminalUnitErrorDescription(errorCode);
        case DeviceType::VendorDependentMode:
            return getVendorDependentModeErrorDescription(errorCode);
        default:
            return "Unkown Device";
    }
}

std::string WosaErrorNamesUtility::getGeneralErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_ALREADY_STARTED:
            return "ALREADY_STARTED";
        case WFS_ERR_API_VER_TOO_HIGH:
            return "API_VER_TOO_HIGH";
        case WFS_ERR_API_VER_TOO_LOW:
            return "API_VER_TOO_LOW";
        case WFS_ERR_CANCELED:
            return "COMMAND_CANCELED";
        case WFS_ERR_CFG_INVALID_HKEY:
            return "CFG_INVALID_HKEY";
        case WFS_ERR_CFG_INVALID_NAME:
            return "CFG_INVALID_NAME";
        case WFS_ERR_CFG_INVALID_SUBKEY:
            return "CFG_INVALID_SUBKEY";
        case WFS_ERR_CFG_INVALID_VALUE:
            return "CFG_INVALID_VALUE";
        case WFS_ERR_CFG_KEY_NOT_EMPTY:
            return "CFG_KEY_NOT_EMPTY";
        case WFS_ERR_CFG_NAME_TOO_LONG:
            return "CFG_NAME_TOO_LONG";
        case WFS_ERR_CFG_NO_MORE_ITEMS:
            return "CFG_NO_MORE_ITEMS";
        case WFS_ERR_CFG_VALUE_TOO_LONG:
            return "CFG_VALUE_TOO_LONG";
        case WFS_ERR_DEV_NOT_READY:
            return "DEVICE_NOT_READY";
        case WFS_ERR_HARDWARE_ERROR:
            return "HARDWARE_ERROR";
        case WFS_ERR_INTERNAL_ERROR:
            return "INTERNAL_ERROR";
        case WFS_ERR_INVALID_ADDRESS:
            return "INVALID_ADDRESS";
        case WFS_ERR_INVALID_APP_HANDLE:
            return "INVALID_APP_HANDLE";
        case WFS_ERR_INVALID_BUFFER:
            return "INVALID_BUFFER";
        case WFS_ERR_INVALID_CATEGORY:
            return "INVALID_CATEGORY";
        case WFS_ERR_INVALID_COMMAND:
            return "INVALID_COMMAND";
        case WFS_ERR_INVALID_EVENT_CLASS:
            return "INVALID_EVENT_CLASS";
        case WFS_ERR_INVALID_HSERVICE:
            return "INVALID_HSERVICE";
        case WFS_ERR_INVALID_HPROVIDER:
            return "INVALID_HPROVIDER";
        case WFS_ERR_INVALID_HWND:
            return "INVALID_HWND";
        case WFS_ERR_INVALID_HWNDREG:
            return "INVALID_HWNDREG";
        case WFS_ERR_INVALID_POINTER:
            return "INVALID_POINTER";
        case WFS_ERR_INVALID_REQ_ID:
            return "INVALID_REQ_ID";
        case WFS_ERR_INVALID_RESULT:
            return "INVALID_RESULT";
        case WFS_ERR_INVALID_SERVPROV:
            return "INVALID_SERVPROV";
        case WFS_ERR_INVALID_TIMER:
            return "INVALID_TIMER";
        case WFS_ERR_INVALID_TRACELEVEL:
            return "INVALID_TRACELEVEL";
        case WFS_ERR_LOCKED:
            return "LOCKED";
        case WFS_ERR_NO_BLOCKING_CALL:
            return "NO_BLOCKING_CALL";
        case WFS_ERR_NO_SERVPROV:
            return "NO_SERVPROV";
        case WFS_ERR_NO_SUCH_THREAD:
            return "NO_SUCH_THREAD";
        case WFS_ERR_NO_TIMER:
            return "NO_TIMER";
        case WFS_ERR_NOT_LOCKED:
            return "NOT_LOCKED";
        case WFS_ERR_NOT_OK_TO_UNLOAD:
            return "NOT_OK_TO_UNLOAD";
        case WFS_ERR_NOT_STARTED:
            return "NOT_STARTED";
        case WFS_ERR_NOT_REGISTERED:
            return "NOT_REGISTERED";
        case WFS_ERR_OP_IN_PROGRESS:
            return "OP_IN_PROGRESS";
        case WFS_ERR_OUT_OF_MEMORY:
            return "OUT_OF_MEMORY";
        case WFS_ERR_SERVICE_NOT_FOUND:
            return "SERVICE_NOT_FOUND";
        case WFS_ERR_SPI_VER_TOO_HIGH:
            return "SPI_VER_TOO_HIGH";
        case WFS_ERR_SPI_VER_TOO_LOW:
            return "SPI_VER_TOO_LOW";
        case WFS_ERR_SRVC_VER_TOO_HIGH:
            return "SRVC_VER_TOO_HIGH";
        case WFS_ERR_SRVC_VER_TOO_LOW:
            return "SRVC_VER_TOO_LOW";
        case WFS_ERR_TIMEOUT:
            return "TIMEOUT";
        case WFS_ERR_UNSUPP_CATEGORY:
            return "UNSUPP_CATEGORY";
        case WFS_ERR_UNSUPP_COMMAND:
            return "UNSUPP_COMMAND";
        case WFS_ERR_VERSION_ERROR_IN_SRVC:
            return "VERSION_ERROR_IN_SRVC";
        case WFS_ERR_INVALID_DATA:
            return "INVALID_DATA";
        case WFS_ERR_SOFTWARE_ERROR:
            return "SOFTWARE_ERROR";
        case WFS_ERR_CONNECTION_LOST:
            return "CONNECTION_LOST";
        case WFS_ERR_USER_ERROR:
            return "USER_ERROR";
        case WFS_ERR_UNSUPP_DATA:
            return "UNSUPP_DATA";
        case WFS_GENERAL_ERROR:
            return "GENERAL_ERROR";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getBarcodeReaderErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_BCR_BARCODEINVALID:
            return "BARCODE_IS_INVALID";
        case WFS_ERR_BCR_INVALID_PORT:
            return "INVALID_PORT";
        case WFS_ERR_BCR_POWERSAVETOOSHORT:
            return "POWER_SAVE_TOO_SHORT";
        case WFS_ERR_BCR_POWERSAVEMEDIAPRESENT:
            return "POWER_SAVE_MEDIA_PRESENT";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getCameraDeviceErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_CAM_CAMNOTSUPP:
            return "NOT_SUPPORTED";
        case WFS_ERR_CAM_MEDIAFULL:
            return "MEDIA_FULL";
        case WFS_ERR_CAM_CAMINOP:
            return "IN_OPERATION";
        case WFS_ERR_CAM_CHARSETNOTSUPP:
            return "CHARSETNOTSUPPORTED";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getCashDispenserErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_CDM_INVALIDCURRENCY:
            return "INVALID_CURRENCY";

        case WFS_ERR_CDM_INVALIDTELLERID:
            return "INVALID_TELLERID";

        case WFS_ERR_CDM_CASHUNITERROR:
            return "CASHUNIT_ERROR";

        case WFS_ERR_CDM_INVALIDDENOMINATION:
            return "INVALID<_DENOMINATION";

        case WFS_ERR_CDM_INVALIDMIXNUMBER:
            return "INVALID_MIX_NUMBER";

        case WFS_ERR_CDM_NOCURRENCYMIX:
            return "NO_CURRENCY_MIX";

        case WFS_ERR_CDM_NOTDISPENSABLE:
            return "NOT_DISPENSABLE";

        case WFS_ERR_CDM_TOOMANYITEMS:
            return "TOO_MANY_ITEMS";

        case WFS_ERR_CDM_UNSUPPOSITION:
            return "UNSUPPORTED_POSITION";

        case WFS_ERR_CDM_SAFEDOOROPEN:
            return "SAFEDOOR_OPEN";

        case WFS_ERR_CDM_SHUTTERNOTOPEN:
            return "SHUTTER_NOT_OPEN";

        case WFS_ERR_CDM_SHUTTEROPEN:
            return "SHUTTER_OPEN";

        case WFS_ERR_CDM_SHUTTERCLOSED:
            return "SHUTTER_CLOSED";

        case WFS_ERR_CDM_INVALIDCASHUNIT:
            return "INVALID_CASHUNIT";

        case WFS_ERR_CDM_NOITEMS:
            return "NO_ITEMS";

        case WFS_ERR_CDM_EXCHANGEACTIVE:
            return "EXCHANGE_ACTIVE";

        case WFS_ERR_CDM_NOEXCHANGEACTIVE:
            return "NOEXCHANGE_ACTIVE";

        case WFS_ERR_CDM_SHUTTERNOTCLOSED:
            return "SHUTTER_NOT_CLOSED";

        case WFS_ERR_CDM_PRERRORNOITEMS:
            return "PR_ERROR_NO_ITEMS";

        case WFS_ERR_CDM_PRERRORITEMS:
            return "PR_ERROR_ITEMS";

        case WFS_ERR_CDM_PRERRORUNKNOWN:
            return "PR_ERROR_UNKNOWN";

        case WFS_ERR_CDM_ITEMSTAKEN:
            return "ITEMS_TAKEN";

        case WFS_ERR_CDM_INVALIDMIXTABLE:
            return "INVALID_MIX_TABLE";

        case WFS_ERR_CDM_OUTPUTPOS_NOT_EMPTY:
            return "OUTPUT_POSITION_NOT_EMPTY";

        case WFS_ERR_CDM_INVALIDRETRACTPOSITION:
            return "INVALID_RETRACT_POSITION";

        case WFS_ERR_CDM_NOTRETRACTAREA:
            return "NO_TRETRACT_AREA";

        case WFS_ERR_CDM_NOCASHBOXPRESENT:
            return "NO_CASHBOX_PRESENT";

        case WFS_ERR_CDM_AMOUNTNOTINMIXTABLE:
            return "AMOUNT_NOTIN_MIXTABLE";

        case WFS_ERR_CDM_ITEMSNOTTAKEN:
            return "ITEMS_NOT_TAKEN";

        case WFS_ERR_CDM_ITEMSLEFT:
            return "ITEMS_LEFT";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getCashInModuleErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_CIM_INVALIDCURRENCY:
            return "INVALID_CURRENCY";

        case WFS_ERR_CIM_INVALIDTELLERID:
            return "INVALID_TELLER_ID";

        case WFS_ERR_CIM_CASHUNITERROR:
            return "CASHUNIT_ERROR";

        case WFS_ERR_CIM_TOOMANYITEMS:
            return "TOOMANY_ITEMS";

        case WFS_ERR_CIM_UNSUPPOSITION:
            return "UNSUPPORTED_POSITION";

        case WFS_ERR_CIM_SAFEDOOROPEN:
            return "SAFEDOOR_OPEN";

        case WFS_ERR_CIM_SHUTTERNOTOPEN:
            return "SHUTTER_NOT_OPEN";

        case WFS_ERR_CIM_SHUTTEROPEN:
            return "SHUTTER_OPEN";

        case WFS_ERR_CIM_SHUTTERCLOSED:
            return "SHUTTER_CLOSED";

        case WFS_ERR_CIM_INVALIDCASHUNIT:
            return "INVALID_CASHUNIT";

        case WFS_ERR_CIM_NOITEMS:
            return "NO_ITEMS";

        case WFS_ERR_CIM_EXCHANGEACTIVE:
            return "EXCHANGE_ACTIVE";

        case WFS_ERR_CIM_NOEXCHANGEACTIVE:
            return "NO_EXCHANGE_ACTIVE";

        case WFS_ERR_CIM_SHUTTERNOTCLOSED:
            return "SHUTTER_NOT_CLOSED";

        case WFS_ERR_CIM_ITEMSTAKEN:
            return "ITEMS_TAKEN";

        case WFS_ERR_CIM_CASHINACTIVE:
            return "CASHIN_ACTIVE";

        case WFS_ERR_CIM_NOCASHINACTIVE:
            return "NO_CASHIN_ACTIVE";

        case WFS_ERR_CIM_POSITION_NOT_EMPTY:
            return "POSITION_NOT_EMPTY";

        case WFS_ERR_CIM_INVALIDRETRACTPOSITION:
            return "INVALID_RETRACT_POSITION";

        case WFS_ERR_CIM_NOTRETRACTAREA:
            return "NO_TRETRACT_AREA";

        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getDepositoryErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_DEP_DEPFULL:
            return "DEPFULL";
        case WFS_ERR_DEP_DEPJAMMED:
            return "DEPJAMMED";
        case WFS_ERR_DEP_ENVEMPTY:
            return "ENVEMPTY";
        case WFS_ERR_DEP_ENVJAMMED:
            return "ENVJAMMED";
        case WFS_ERR_DEP_ENVSIZE:
            return "ENVSIZE";
        case WFS_ERR_DEP_NOENV:
            return "NOENV";
        case WFS_ERR_DEP_PTRFAIL:
            return "PTRFAIL";
        case WFS_ERR_DEP_SHTNOTCLOSED:
            return "SHTNOTCLOSED";
        case WFS_ERR_DEP_SHTNOTOPENED:
            return "SHTNOTOPENED";
        case WFS_ERR_DEP_CONTMISSING:
            return "CONTMISSING";
        case WFS_ERR_DEP_DEPUNKNOWN:
            return "DEPUNKNOWN";
        case WFS_ERR_DEP_CHARSETNOTSUPP:
            return "CHARSETNOTSUPP";
        case WFS_ERR_DEP_TONEROUT:
            return "TONEROUT";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getIdentificationCardErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_IDC_MEDIAJAM:
            return "MEDIA_JAM";
        case WFS_ERR_IDC_NOMEDIA:
            return "NO_MEDIA";
        case WFS_ERR_IDC_MEDIARETAINED:
            return "MEDIA_RETAINED";
        case WFS_ERR_IDC_RETAINBINFULL:
            return "RETAINBIN_FULL";
        case WFS_ERR_IDC_INVALIDDATA:
            return "INVALID_DATA";
        case WFS_ERR_IDC_INVALIDMEDIA:
            return "INVALID_MEDIA";
        case WFS_ERR_IDC_FORMNOTFOUND:
            return "FORM_NOT_FOUND";
        case WFS_ERR_IDC_FORMINVALID:
            return "FORM_INVALID";
        case WFS_ERR_IDC_DATASYNTAX:
            return "DATA_SYNTAX";
        case WFS_ERR_IDC_SHUTTERFAIL:
            return "SHUTTER_FAIL";
        case WFS_ERR_IDC_SECURITYFAIL:
            return "SECURITY_FAIL";
        case WFS_ERR_IDC_PROTOCOLNOTSUPP:
            return "PROTOCOL_NOT_SUPP";
        case WFS_ERR_IDC_ATRNOTOBTAINED:
            return "ATRNOTOBTAINED";
        case WFS_ERR_IDC_INVALIDKEY:
            return "INVALID_KEY";
        case WFS_ERR_IDC_WRITE_METHOD:
            return "WRITE_METHOD";
        case WFS_ERR_IDC_CHIPPOWERNOTSUPP:
            return "CHIP_POWER_NOT_SUPPORTED";
        case WFS_ERR_IDC_CARDTOOSHORT:
            return "CARD_TOOSHORT";
        case WFS_ERR_IDC_CARDTOOLONG:
            return "CARD_TOOLONG";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getPINKeypadDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_PIN_KEYNOTFOUND:
            return "KEY_NOT_FOUND";
        case WFS_ERR_PIN_MODENOTSUPPORTED:
            return "MODE_NOT_SUPPORTED";
        case WFS_ERR_PIN_ACCESSDENIED:
            return "IN_ACCESSDENIED:";
        case WFS_ERR_PIN_INVALIDID:
            return "INVALID_ID";
        case WFS_ERR_PIN_DUPLICATEKEY:
            return "DUPLICATE_KEY";
        case WFS_ERR_PIN_KEYNOVALUE:
            return "KEY_NO_VALUE";
        case WFS_ERR_PIN_USEVIOLATION:
            return "USE_VIOLATION";
        case WFS_ERR_PIN_NOPIN:
            return "NO_PIN";
        case WFS_ERR_PIN_INVALIDKEYLENGTH:
            return "INVALID_KEY_LENGTH";
        case WFS_ERR_PIN_KEYINVALID:
            return "KEY_INVALID";
        case WFS_ERR_PIN_KEYNOTSUPPORTED:
            return "KEY_NOT_SUPPORTED";
        case WFS_ERR_PIN_NOACTIVEKEYS:
            return "NO_ACTIVE_KEYS";
        case WFS_ERR_PIN_NOTERMINATEKEYS:
            return "NO_TERMINATE_KEYS";
        case WFS_ERR_PIN_MINIMUMLENGTH:
            return "MINIMUM_LENGTH";
        case WFS_ERR_PIN_PROTOCOLNOTSUPP:
            return "PROTOCOL_NOT_SUPPORTED";
        case WFS_ERR_PIN_INVALIDDATA:
            return "INVALID_DATA";
        case WFS_ERR_PIN_NOTALLOWED:
            return "NOT_ALLOWED";
        case WFS_ERR_PIN_NOKEYRAM:
            return "NO_KEY_RAM";
        case WFS_ERR_PIN_NOCHIPTRANSACTIVE:
            return "NO_CHIP_TRANSACTIVE";
        case WFS_ERR_PIN_ALGORITHMNOTSUPP:
            return "ALGORITHM_NOT_SUPPORTED";
        case WFS_ERR_PIN_FORMATNOTSUPP:
            return "FORMAT_NOT_SUPPPRTED";
        case WFS_ERR_PIN_HSMSTATEINVALID:
            return "HSM_STATE_INVALID";
        case WFS_ERR_PIN_MACINVALID:
            return "MAC_INVALID";
        case WFS_ERR_PIN_PROTINVALID:
            return "PROTOCOL_INVALID";
        case WFS_ERR_PIN_FORMATINVALID:
            return "FORMAT_INVALID";
        case WFS_ERR_PIN_CONTENTINVALID:
            return "CONTENT_INVALID";
        case WFS_ERR_PIN_SIG_NOT_SUPP:
            return "SIG_NOT_SUPP";
        case WFS_ERR_PIN_INVALID_MOD_LEN:
            return "INVALID_MOD_LEN";
        case WFS_ERR_PIN_INVALIDCERTSTATE:
            return "INVALID_CERT_STATE";
        case WFS_ERR_PIN_KEY_GENERATION_ERROR:
            return "KEY_GENERATION_ERROR";
        case WFS_ERR_PIN_EMV_VERIFY_FAILED:
            return "EMV_VERIFY_FAILED";
        case WFS_ERR_PIN_RANDOMINVALID:
            return "PIN_RANDOMINVALID";
        case WFS_ERR_PIN_SIGNATUREINVALID:
            return "SIGNATURE_INVALID";
        case WFS_ERR_PIN_SNSCDINVALID:
            return "SNSCD_INVALID";
        case WFS_ERR_PIN_NORSAKEYPAIR:
            return "NO_RSA_KEY_PAIR";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getPrinterErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_PTR_FORMNOTFOUND:
            return "FORM_NOT_FOUND";
        case WFS_ERR_PTR_FIELDNOTFOUND:
            return "FIEL_DNOT_FOUND";
        case WFS_ERR_PTR_NOMEDIAPRESENT:
            return "NO_MEDIA_PRESENT";
        case WFS_ERR_PTR_READNOTSUPPORTED:
            return "READ_NOT_SUPPORTED";
        case WFS_ERR_PTR_FLUSHFAIL:
            return "FLUSH_FAIL";
        case WFS_ERR_PTR_MEDIAOVERFLOW:
            return "MEDIA_OVERFLOW";
        case WFS_ERR_PTR_FIELDSPECFAILURE:
            return "FIEL_DSPEC_FAILURE";
        case WFS_ERR_PTR_FIELDERROR:
            return "FIELD_ERROR";
        case WFS_ERR_PTR_MEDIANOTFOUND:
            return "MEDIA_NOT_FOUND";
        case WFS_ERR_PTR_EXTENTNOTSUPPORTED:
            return "EXTENT_NOT_SUPPORTED";
        case WFS_ERR_PTR_MEDIAINVALID:
            return "MEDIA_INVALID";
        case WFS_ERR_PTR_FORMINVALID:
            return "FORM_INVALID";
        case WFS_ERR_PTR_FIELDINVALID:
            return "FIELDINVALID";
        case WFS_ERR_PTR_MEDIASKEWED:
            return "MEDIA_SKEWED";
        case WFS_ERR_PTR_RETRACTBINFULL:
            return "RETRACTBIN_FULL";
        case WFS_ERR_PTR_STACKERFULL:
            return "STACKER_FULL";
        case WFS_ERR_PTR_PAGETURNFAIL:
            return "PAGE_TURN_FAIL";
        case WFS_ERR_PTR_MEDIATURNFAIL:
            return "MEDIA_TURN_FAIL";
        case WFS_ERR_PTR_SHUTTERFAIL:
            return "SHUTTER_FAIL";
        case WFS_ERR_PTR_MEDIAJAMMED:
            return "MEDIA_JAMMED";
        case WFS_ERR_PTR_FILE_IO_ERROR:
            return "FILE_IO_ERROR";
        case WFS_ERR_PTR_CHARSETDATA:
            return "CHAR_SET_DATA";
        case WFS_ERR_PTR_PAPERJAMMED:
            return "PAPER_JAMMED";
        case WFS_ERR_PTR_PAPEROUT:
            return "PAPER_OUT";
        case WFS_ERR_PTR_INKOUT:
            return "INK_OUT";
        case WFS_ERR_PTR_TONEROUT:
            return "TONER_OUT";
        case WFS_ERR_PTR_LAMPINOP:
            return "LAMP_INOPPERATION";
        case WFS_ERR_PTR_SOURCEINVALID:
            return "SOURCE_INVALID";
        case WFS_ERR_PTR_SEQUENCEINVALID:
            return "SEQUENCE_INVALID";
        case WFS_ERR_PTR_MEDIASIZE:
            return "MEDIA_SIZE";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getSensorsAndIndicatorsUnitErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_SIU_INVALID_PORT:
            return "INVALID_PORT";
        case WFS_ERR_SIU_SYNTAX:
            return "SYNTAX";
        case WFS_ERR_SIU_PORT_ERROR:
            return "PORT_ERROR:";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getTextTerminalUnitErrorDescription(HRESULT errorCode)
{
    switch (errorCode)
    {
        case WFS_ERR_TTU_FIELDERROR:
            return "FIELD_ERROR";
        case WFS_ERR_TTU_FIELDINVALID:
            return "FIELDINVALID";
        case WFS_ERR_TTU_FIELDNOTFOUND:
            return "FIELDNOTFOUND";
        case WFS_ERR_TTU_FIELDSPECFAILURE:
            return "FIELDSPECFAILURE";
        case WFS_ERR_TTU_FORMINVALID:
            return "FORMI_NVALID";
        case WFS_ERR_TTU_FORMNOTFOUND:
            return "FORM_NOT_FOUND";
        case WFS_ERR_TTU_INVALIDLED:
            return "INVALIDLED";
        case WFS_ERR_TTU_KEYCANCELED:
            return "KEYCANCELED";
        case WFS_ERR_TTU_MEDIAOVERFLOW:
            return "MEDIA_OVERFLOW";
        case WFS_ERR_TTU_RESNOTSUPP:
            return "RESNOTSUPP";
        case WFS_ERR_TTU_CHARSETDATA:
            return "CHARSETDATA";
        case WFS_ERR_TTU_KEYINVALID:
            return "KEYINVALID";
        case WFS_ERR_TTU_KEYNOTSUPPORTED:
            return "KEYNOTSUPPORTED";
        case WFS_ERR_TTU_NOACTIVEKEYS:
            return "NOACTIVEKEYS";
        default:
            return "Unkown Error";
    }
}

std::string WosaErrorNamesUtility::getVendorDependentModeErrorDescription(HRESULT errorCode)
{
    return "General Error";
}
