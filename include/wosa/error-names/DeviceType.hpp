#ifndef DEVICE_TYPE_HPP
#define DEVICE_TYPE_HPP

#include <string>

enum class DeviceType
{
    IdentificationCard = 0,   // IDC
    CashDispenserModule,      // CDM
    TextTerminalUnit,         // TTU
    JournalPrinter,           // JPTR
    ReceiptPrinter,           // RPTR
    PINKeypad,                // PIN
    Depository,               // DEP
    SensorsAndIndicatorsUnit, // SIU
    CameraDevice,             // CAM
    StatementPrinter,         // SPTR
    PassbookPrinter,          // PPTR
    BarcodeReader,            // BCR
    VendorDependentMode,      // VDM
    CashInModule,             // CIM
    Printer,                  // PTR
    VacuumFluorescentDisplay, // VFD
    UnknownDeviceType
};

static const std::string DeviceTypeString[] = {"IDC", "CDM", "TTU", "JPTR", "RPTR", "PIN", "DEP", "SIU", "CAM", "SPTR", "PPTR", "BCR", "VDM", "CIM", "PTR", "VFD", "UNKNOWN"};

#endif // DEVICE_TYPE_HPP
