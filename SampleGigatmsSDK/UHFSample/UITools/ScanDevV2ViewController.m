//
//  ScanDevV2ViewController.m
//  UHFSample
//
//  Created by Gianni on 2019/8/27.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import "ScanDevV2ViewController.h"

#import "DevDetailTabBarViewController.h"
#import "BaseDevItemTableViewCell.h"
#import <UHFSDK/UHFScanner.h>
#import <UHFSDK/UHFDevice.h>
#import <UHFSDK/GTDeviceManager.h>

//#import <Crashlytics/Crashlytics.h>

//extern NSMutableArray* g_BaseDevs;

@interface ScanDevV2ViewController ()<UIPickerViewDelegate,UIPickerViewDataSource,
UITableViewDelegate, UITableViewDataSource,
UHFScannerCallback,DevConnectionCallback>
{
    NSArray *_pickDataDevClass;
    NSArray *_pickDataDevConChannl;
    NSMutableArray* g_BaseDevs;
    NSMutableDictionary* allBaseDevList;
    UHFScanner* uhfScanner;
}
@end

@implementation ScanDevV2ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    _pickDataDevClass = @[@"UR0250", @"TS100", @"TS800", @"PWD100"];
    
    _pickDataDevConChannl = @[@"Wifi", @"BLE"];
    
    self.pickerDevClass.dataSource = self;
    self.pickerDevClass.delegate = self;
    [self.pickerDevClass setTag:1];
    
   
     [self.pickerDevClass selectRow:1 inComponent:0 animated:true];
    self.pickerDevConChannl.dataSource = self;
    self.pickerDevConChannl.delegate = self;
    [self.pickerDevConChannl setTag:2];
    
    
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    uhfScanner = [[UHFScanner alloc]init:self ClassVer:UHF_TS100];
    allBaseDevList = [[NSMutableDictionary alloc]init];
    
    if (g_BaseDevs == nil) {
        g_BaseDevs = [[NSMutableArray alloc] init];
    }
    
    [self showAPPSDKVersion];
}

- (void)viewWillAppear:(BOOL)animated {
     [self refresh];
}

- (void)showAPPSDKVersion {
    NSString * appVersionString = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
    NSString * appBuildString = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"];
    
    
    NSDictionary *infoDictionary = [[NSBundle bundleForClass: [UHFScanner class]] infoDictionary];
    NSString *version = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
    NSString *build = [infoDictionary objectForKey:(NSString *)kCFBundleVersionKey];
    NSString *fVersion = [NSString stringWithFormat:@"%@.%@",version,build];
    
    NSString * versionBuildString = [NSString stringWithFormat:@"APP Ver: %@.%@, SDK Ver: %@", appVersionString, appBuildString, fVersion];
    NSLog(@"%@",versionBuildString);
    [_txtAppVer setText:versionBuildString];
    
    
    
}

- (IBAction)actScan:(id)sender {
    [g_BaseDevs removeAllObjects];
    [[GTDeviceManager sharedDeviceManager]removeAllDevice];
    
    
    int devClass = (int)[self.pickerDevClass selectedRowInComponent:0];
    ClassVer classVer;
    switch (devClass) {
        case 0:
        {
            classVer = UHF_UR0250;
        }
            break;
        case 1:
        {
            classVer = UHF_TS100;
        }
            break;
        case 2:
        {
            classVer = UHF_TS800;
        }
            break;
        case 3:
        {
            classVer = UHF_PWD100;
        }
            break;
            
        default:
            classVer = UHF_UR0250;
            break;
    }
    
    [uhfScanner changeClassVer:classVer];
    
    int devConChannl = (int)[self.pickerDevConChannl selectedRowInComponent:0];
    switch (devConChannl) {
        case 0:
        {
            [uhfScanner changeConnectType:Type_WiFi_UDP];
        }
            break;
        case 1:
        {
            [uhfScanner changeConnectType:Type_BLE];
        }
            break;
            
        default:
            break;
    }
    
    [uhfScanner startScanDevice];
    
}

- (NSInteger)numberOfComponentsInPickerView:(nonnull UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(nonnull UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    NSInteger iCount;
    switch (pickerView.tag) {
        case 1:
        {
            iCount = _pickDataDevClass.count;
        }
            
            break;
            
        case 2:
        {
            iCount = _pickDataDevConChannl.count;
            
        }
            break;
            
            
        default:
            iCount = 0;
            break;
    }
    return iCount;
}

- (NSString*)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    
    NSString *strValue;
    switch (pickerView.tag) {
        case 1:
        {
            strValue = _pickDataDevClass[row];
            
        }
            break;
        case 2:
        {
            strValue = _pickDataDevConChannl[row];
            
        }
            break;
        default:
            strValue = @"";
            break;
    }
    return strValue;
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component{
    
}



#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return g_BaseDevs.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    BaseDevItemTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"BaseDevScanCell" forIndexPath:indexPath];
    
    BaseDevice* temp = [g_BaseDevs objectAtIndex:indexPath.row];
    
    if (temp) {
        cell.labDevName.text = temp.getDevInfo.devName;
        cell.labDevInfo.text = temp.getDevInfo.devUidInfo;
        cell.labConnStauts.text = temp.getDevInfo.strConnStauts;
        [cell.btnConnect setTag:indexPath.row];
        switch (temp.getDevInfo.currentConnStatus) {
            case DevDisconnected:
            {
                 [cell.btnConnect setTitle:@"Connect" forState:UIControlStateNormal];
            }
                break;
            case DevConnected:
            {
                 [cell.btnConnect setTitle:@"Disconnect" forState:UIControlStateNormal];
            }
                break;
            default:
            {
                [cell.btnConnect setTitle:@"Connect" forState:UIControlStateNormal];
            }
                break;
        }
        [cell.btnConnect addTarget:self
                            action:@selector(actConnect:) forControlEvents:UIControlEventTouchDown];
        
        [cell.btnCtrl setTag:indexPath.row];
        [cell.btnCtrl addTarget:self
                         action:@selector(actCtrl:) forControlEvents:UIControlEventTouchDown];
        
    }
    return cell;
}

-(void)actCtrl:(id)sender{
    if (g_BaseDevs) {
        BaseDevice* temp = [g_BaseDevs objectAtIndex:[sender tag]];
        if (temp) {
            UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
            DevDetailTabBarViewController* ctrler =[storyboard instantiateViewControllerWithIdentifier:@"DevDetailCtrl"];
            [ctrler setPassDev:((UHFDevice*)temp)];
            ctrler.title = temp.getDevInfo.devName;
            
            [self.navigationController pushViewController:ctrler animated:YES];
        }
    }
    
    
    
}
-(void)actConnect:(id)sender{
    if (g_BaseDevs) {
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
            
            
            [self refresh];
        }
    }
    
}

-(void)didScanStop{
    
}
-(void)didDiscoverDevice:(BaseDevice*)dev{
    NSLog(@"UI didDiscoverDevice dev = %@",dev.debugDescription);
    GTBaseDevInfo* devInfo = dev.getDevInfo;
    BaseDevice* addDev = [[GTDeviceManager sharedDeviceManager]addDevice:devInfo];
    if(addDev) {
        [addDev setConnCallback:self];
        if(g_BaseDevs) {
            [g_BaseDevs addObject:addDev];
        }
        
    }
    [self refresh];
}
-(void)didError:(NSString*)strError{
    
}

- (void)didUpdateConnectionStatus:(BaseDevice*)dev Status:(GTDevConnStatus) connectedState err_code:(int)nErrCode{
    [self refresh];
}

-(void)refresh{
//    self.tableView.delegate = self;
//    self.tableView.dataSource = self;
    [self.tableView reloadData];
    self.tableView.contentInset = UIEdgeInsetsMake(0, -10, 0, 10);
}

@end
