//
//  IUHFDeviceListener.h
//  UHFSDK
//
//  Created by Gianni on 2019/3/27.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GNPTagInfo.h"
#import "GNPDecodedTagData.h"

NS_ASSUME_NONNULL_BEGIN





typedef NS_ENUM(Byte, LockAction){
    LA_UNLOCK          = 0x00,
    LA_LOCK            = 0x01,
    LA_PERMA_UNLOCK    = 0x02,
    LA_PERMA_LOCK      = 0x03,
};

typedef NS_ENUM(Byte, MemoryBank){
    MBC_Reserve          = 0x00,
    MBC_EPC              = 0x01,
    MBC_TID              = 0x02,
    MBC_UserMemory       = 0x03,
    MBC_KILL_PASSWORD    = 0x04,
    MBC_ACCESS_PASSWORD  = 0x05,
};

typedef NS_ENUM(Byte, MemoryBankSelection){
    
    MBS_EPC         = 0x02,
    MBS_TID         = 0x04,
    MBS_PC_EPC      = 0x03,
    MBS_EPC_TID     = 0x06,
    MBS_PC_EPC_TID  = 0x07,
    MBS_EPC_ASCII   = 0x08,
};

typedef NS_ENUM(Byte, EventType){
    
    ET_TagPresented             = 0xFE,
    ET_TagPresentedWithRemoved  = 0xDE,
    ET_TagPresentedEx           = 0x00,
};


typedef NS_ENUM(Byte, KeyboardSimulation){
    
    KS_DISABLE      = 0x00,
    KS_HID_KEYBOARD = 0x03,
    KS_BLE_KEYBOARD = 0x05,
};


/**
 multiple
 
 - OI_TCP_SERVER_1_0: TS800 UR0250
 - OI_Default_1_0: TS800 UR0250
 - OI_HID_N_VCOM: HID
 - OI_BLE: BLE
 - OI_TCP_CLIENT: TCP Client
 - OI_TCP_SERVER: TCP Server
 */
typedef NS_ENUM(Byte, OutputInterface){
    OI_TCP_SERVER_1_0     = 0x04,
    OI_Default_1_0        = 0xFF,
    OI_HID_N_VCOM           = 0x08,
    OI_BLE                  = 0x10,
    OI_TCP_CLIENT           = 0x20,
    OI_TCP_SERVER           = 0x40,
};

typedef NS_ENUM(Byte, PostDataDelimiter){
    
    PDD_NONE            = 0x00,
    PDD_CARRIAGE        = 0x10,
    PDD_LINE            = 0x20,
    PDD_CARRIAGE_LINE   = 0x30,
    PDD_TAB             = 0x40,
};

typedef NS_ENUM(Byte, ActiveMode){
    AM_READ                     = 0x00,
    AM_COMMAND                  = 0x01,
    AM_TAG_ANALYSIS             = 0x04,
    AM_VERIFY                   = 0x05,
    AM_ENCODE                   = 0x06,
    AM_CUSTOMIZED_READ          = 0x07,
    AM_DEACTIVATE               = 0x08,
    AM_REACTIVATE               = 0x09,
    AM_DEACTIVATE_USER_BANK     = 0x0A,
    AM_REACTIVATE_USER_BANK     = 0x0B,
};

typedef NS_ENUM(Byte, TagDataEncodeType){
    TDE_UDC             = 0x01,
    TDE_EAN_UPC_EAS     = 0x02,
    TDE_EAN_UPC         = 0x04,
    TDE_RAW_DATA        = 0x08,
};
/**
 Specifies the repeats mode of sounding the buzzer.
 
 - BOM_Off: Selects to turn off beep sound
 - BOM_Once: Selects to sound the beep once
 - BOM_Repeat: Selects to repeatly sound the beep
 */
typedef NS_ENUM(Byte, BuzzerOperationMode){
    BOM_Off              = 0x00,
    BOM_Once      = 0x7F,
    BOM_Repeat        = 0xFF,
    
};


/**
 Target
 
 - A: Tagget A selected for S0 to S3.
 - B: Tagget B selected for S0 to S3.
 - A_B: Toggle target A, B for S0 to S3.
 - deSL: Target A selected for SL session.
 - SL: Target B selected for SL session.
 - SL_deSL: Toggle target A, B for SL session.
 */
typedef NS_ENUM(Byte, Target){
    A              = 0x00,
    B              = 0x01,
    A_B            = 0x02,
    deSL           = 0x00,
    SL             = 0x01,
    SL_deSL        = 0x02,
};



/**
 Session
 
 - S0: Session 0 is selected for an inventory round.
 - S1: Session 1 is selected for an inventory round.
 - S2: Session 2 is selected for an inventory round.
 - S3: Session 3 is selected for an inventory round.
 - Session_SL: A selected flag, SL, which a reader may assert or deassert using a Select command.
 */
typedef NS_ENUM(Byte, Session){
    S0              = 0x00,
    S1              = 0x01,
    S2              = 0x02,
    S3              = 0x03,
    Session_SL              = 0x04,
    
};

/**
 TriggerType
 
 - Command: Command  Trigger
 - DigitalInput: DigitalInput  Trigger
 - Sensor: Sensor  Trigger
 - SensorAndDigitalInput: SensorAndDigitalInput  Trigger
 */
typedef NS_ENUM(Byte, TriggerType){
    
    Command                    = 0x01,
    DigitalInput               = 0x02,
    Sensor                     = 0x04,
    SensorAndDigitalInput      = 0x06,
};


/**
 RfSensitivityLevel
 
 - LEVEL_14_HIGHEST: The highest sensitivity level 14.
 - LEVEL_13: The sensitivity level 13.
 - LEVEL_12: The sensitivity level 12.
 - LEVEL_11: The sensitivity level 11.
 - LEVEL_10: The sensitivity level 10.
 - LEVEL_9: The sensitivity level 9.
 - LEVEL_8: The sensitivity level 8.
 - LEVEL_7: The sensitivity level 7.
 - LEVEL_6: The sensitivity level 6.
 - LEVEL_5: The sensitivity level 5.
 - LEVEL_4: The sensitivity level 4.
 - LEVEL_3: The sensitivity level 3.
 - LEVEL_2: The sensitivity level 2.
 - LEVEL_1_LOWEST: The lowest sensitivity level 1.
 */
typedef NS_ENUM(Byte, RfSensitivityLevel){
    LEVEL_14_HIGHEST    = (Byte) -90,
    LEVEL_13            = (Byte) -87,
    LEVEL_12            = (Byte) -84,
    LEVEL_11            = (Byte) -81,
    LEVEL_10            = (Byte) -80,
    LEVEL_9             = (Byte) -77,
    LEVEL_8             = (Byte) -74,
    LEVEL_7             = (Byte) -71,
    LEVEL_6             = (Byte) -68,
    LEVEL_5             = (Byte) -65,
    LEVEL_4             = (Byte) -63,
    LEVEL_3             = (Byte) -60,
    LEVEL_2             = (Byte) -57,
    LEVEL_1_LOWEST      = (Byte) -54
};

@protocol IUHFDeviceListener <NSObject>

@optional
/**
 The operating of invokeApi is success.
 
 @param strCMDName CMD Name
 */
-(void)didGeneralSuccess:(NSString*)strCMDName;

/**
 The operating of invokeApi is error.
 Notifies the application that an error has been detected and a suitable response is necessary to process the error condition.
 
 @param strCMDName CMD Name
 @param strErrorMessage Error Message
 */
-(void)didGeneralERROR:(NSString*)strCMDName ErrMessage:(NSString*)strErrorMessage;

/**
 Callback of cmdGetFirmwareVersion
 
 @param fwVer The firmware version of the remote device.
 */
-(void)didGetFirmwareVersion:(NSString*)fwVer;


/**
 Callback of cmdGetBLEFirmwareVersion
 
 @param fwVer The firmware version of the remote device.
 */
-(void)didGetBLEFirmwareVersion:(NSString*)fwVer;
/**
 Callback of cmdGetBLEDeviceName
 
 @param devName The firmware name of the remote device.
 */
-(void)didGetBLEDeviceName:(NSString*)devName;
/**
 Callback of GetRfPower
 
 @param rfPower rf power of TX
 */
-(void)didGetRfPower:(int)rfPower;

/**
 Callback of GetSensitivity
 
 @param rfSensitivity sensitivity of RX
 */
-(void)didGetSensitivity:(RfSensitivityLevel)rfSensitivity;

/**
 only TS800 & UR0250
 Callback of GetTriggerType
 
 @param triggerType The trigger source of inventory.
 */
-(void)didGetTriggerType:(TriggerType)triggerType;

/**
 Callback of GetFrequencyList
 
 @param frequencys The frequency list of TX RF
 */
-(void)didGetFrequencyList:(NSArray*)frequencys;

/**
 Callback of ReadEPC
 
 @param data the Tag data which is going to write to the tag.
 */
-(void)didReadTag:(NSData*)data;



///**
// Callback of GetTarget
//
// @param target <#target description#>
// */
//-(void)didGetTarget:(Target) target;
//
///**
// Callback of GetTarget
//
// @param session <#session description#>
// */
//-(void)didGetSession:(Session)session;

-(void)didGetSessionAnd:(Session)session Target:(Target) target;

/**
 Callback of GetQValue
 
 @param qValue <#qValue description#>
 */
-(void)didGetQValue:(Byte) qValue;

/**
 Callback of GetBuzzerOperationMode
 
 @param bom Buzzer Operation Mode
 */
-(void)didGetBuzzerOperationMode:(BuzzerOperationMode) bom;



/**
 Indicates that the reader reads a new tag.
 If the remote device is invertory and has detected a tag.
 @param taginfo The tag which is inventoried.
 */
-(void)didEventTagPresented:(GNPTagInfo*)taginfo;
-(void)didDiscoverTagInfoEx:(GNPDecodedTagData*) decodedTagData;
/**
 
 @param taginfo The tag which is inventoried.
 */
-(void)didEventTagRemoved:(GNPTagInfo*)taginfo;

/**
 Callback of didGetTagPresentRepeatInterval
 
 @param period Unit: 0.1 seconds
 0: Immediately
 1~253: 0.1~25.3 seconds
 *254: Never repeat
 */

-(void)didGetTagPresentRepeatInterval:(int) period;
-(void)didGetTagRemoveThreshold:(int) missingInventoryThreshold;

-(void)didGetInventoryRoundInterval:(int) tenMilliSeconds;


#pragma mark - Special Command Callback
/**
 * Callback function of `getFilterType`
 * <p>
 * Supported: TS100
 *
 * @param tagDataEncodeTypes Filter of Inventory Event Ex.
 */
-(void)didGetFilter:(TagDataEncodeType) tagDataEncodeTypes;


/**
 * Callback function of `getPostDataDelimiterAndMemoryBankSelection`
 * <p>
 * Supported: TS100
 *
 * @param postDataDelimiter Specifies the delimiter append to the end of output data.
 * @param memoryBankSelection Memory Bank Selection setting.
 */
-(void)didGetPostDataDelimiter:(PostDataDelimiter) postDataDelimiter MemoryBankSelection:(MemoryBankSelection) memoryBankSelection;


/**
 * Callback function of `UHFDevice.getEventType`
 * <p>
 * Supported: TS800, UR0250
 *
 * @param eventType The event command is in simple mode type.
 */
-(void)didGetEventType:(EventType) eventType;

/**
 * Callback function of getOutputInterfaces
 * <p>
 * Supported: TS100
 * @param keyboardSimulation Specifies the data keyboard simulation.
 * @param outputInterfaces Specifies the data output interface.
 */
-(void)didGet:(KeyboardSimulation) keyboardSimulation OutputInterfaces:(OutputInterface) outputInterfaces;


/// Callback function of GetInventoryActiveMode
/// @param activeMode Specifies the data  active mode
-(void)didGetInventoryActiveMode:(ActiveMode) activeMode;

@end

NS_ASSUME_NONNULL_END
