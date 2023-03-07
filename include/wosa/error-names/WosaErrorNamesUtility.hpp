#ifndef WOSA_ERROR_NAMES_UTILITY_HPP
#define WOSA_ERROR_NAMES_UTILITY_HPP

#include <Windows.h>
#include <string>

#include "DeviceType.hpp"

class WosaErrorNamesUtility
{

public:
    static std::string getHResultDescription(DeviceType deviceType, HRESULT errorCode);

private:
    static std::string getGeneralErrorDescription(HRESULT errorCode);
    static std::string getBarcodeReaderErrorDescription(HRESULT errorCode);
    static std::string getCameraDeviceErrorDescription(HRESULT errorCode);
    static std::string getCashDispenserErrorDescription(HRESULT errorCode);
    static std::string getCashInModuleErrorDescription(HRESULT errorCode);
    static std::string getDepositoryErrorDescription(HRESULT errorCode);
    static std::string getIdentificationCardErrorDescription(HRESULT errorCode);
    static std::string getPrinterErrorDescription(HRESULT errorCode);
    static std::string getPINKeypadDescription(HRESULT errorCode);
    static std::string getSensorsAndIndicatorsUnitErrorDescription(HRESULT errorCode);
    static std::string getTextTerminalUnitErrorDescription(HRESULT errorCode);
    static std::string getVendorDependentModeErrorDescription(HRESULT errorCode);
};

#endif // WOSA_ERROR_NAMES_UTILITY_HPP
