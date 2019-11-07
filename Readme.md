GIGATMS SDK for iOS Objective C
===============================

Introduction
------------

The GIGA-TMS UHF SDK sample shows a list of available devices and provides an interface to connect and communication.

Pre-requisites
--------------

-	iOS 10.+
-	Xcode 8+

Getting Started
---------------

This sample uses the Xcode. To build this project, use "Import frameworks" in Xcode.

Capabilities
------------

The SDK Library has the following capabilities:

-	Start and stop the inventory process.

-	Read and write tag data.

-	Configures the UHF reader settings.

Model
-----

The general device behavior model of the UHF reader is:

-	Use StartInventory to start inventory process using specified method of triggering RF power to read tag data.

-	The read tag data is presented at OnTagPresented event.

-	Use StopInventory() to stop inventory process.

##### TS800 Reader

-	The I/O state properties of InputPin0State, OutputPin0State, OutputPin1State, OutputPin2State needs to be updated by calling the method of GetIOState or SetIOState.

Tutorials
---------

This tutorials will give you straight-and-simple 1-2-3 style operations about the usage of SDK library.

This article don't involve too much details. If you need comprehensive understanding, please read the complete manual topic, and not just the tutorial.

##### Scan Device

```
UHFScanner* uhfScanner = [[UHFScanner alloc]init:UHFScannerCallback ClassVer:UHF_UR0250];
[uhfScanner startScanDevice];
```

Scanner Callback:

```
@protocol UHFScannerCallback <NSObject>
@optional
-(void)didScanStop;
-(void)didDiscoverDevice:(BaseDevice*)dev;
-(void)didError:(NSString*)strError;
@end
```

##### Connect to Device

```
BaseDevice* temp = [g_BaseDevs objectAtIndex:[sender tag]];
    if (temp) {
        switch (temp.getDevInfo.currentConnStatus) {
            case DevDisconnected:
            {
                [temp Connect];
            }
                break;
            case DevConnected:
            {
                [temp DisConnect];
            }
                break;
            default:
                 [temp DisConnect];
                break;
        }

        [self refresh];//refresh UI
    }
```

Connection callback:

```
@protocol DevConnectionCallback <NSObject>
@optional
- (void)didUpdateConnectionStatus:(BaseDevice*)dev Status:(GTDevConnStatus) connectedState err_code:(int)nErrCode;
@end
```

##### Start Inventory

Receive also see IUHFDeviceListener

```
 UHFDevice* passDev = get...;
 [passDev cmdStartInventory:ET_PC_EPC];
```

Device command and event Callback

```
@protocol IUHFDeviceListener <NSObject>

-(void)didGeneralSuccess:(NSString*)strCMDName;
-(void)didGeneralERROR:(NSString*)strCMDName ErrMessage:(NSString*)strErrorMessage;
-(void)didDeviceInformation:(NSString*)fwVer;
-(void)didGetRfPower:(int)rfPower;
-(void)didGetSensitivity:(RfSensitivityLevel)rfSensitivity;
-(void)didGetTriggerType:(TriggerType)triggerType;
-(void)didGetFrequencyList:(NSArray*)frequencys;
-(void)didReadTag:(NSData*)data;
-(void)didGetSessionAnd:(Session)session Target:(Target) target;
-(void)didGetQValue:(Byte) qValue;
-(void)didGetBuzzerOperationMode:(BuzzerOperationMode) bom;
-(void)didEventTagPresented:(GNPTagInfo*)taginfo;
-(void)didEventTagRemoved:(GNPTagInfo*)taginfo;
@end
```

See the iOS UFH SDK Documentation for more instructions.

Support
-------

[Related download](ftp://vip:26954214@ftp.gigatms.com.tw/public/disks/disk5472/index.html)

[License](ftp://vip:26954214@ftp.gigatms.com.tw/public/disks/common/Documents/SOFTWARE_DEMOSTRATION_LICENSE_TM970228.pdf)
-------------------------------------------------------------------------------------------------------------------------

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the [License](ftp://vip:26954214@ftp.gigatms.com.tw/public/disks/common/Documents/SOFTWARE_DEMOSTRATION_LICENSE_TM970228.pdf).
