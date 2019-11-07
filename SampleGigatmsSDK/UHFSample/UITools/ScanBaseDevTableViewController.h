//
//  ScanBaseDevTableViewController.h
//  UHFSample
//
//  Created by Gianni on 2019/4/2.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ScanBaseDevTableViewController : UITableViewController
@property (weak, nonatomic) IBOutlet UISwitch *swScanDev;

@property (weak, nonatomic) IBOutlet UISwitch *swUseWiFi;

@end

NS_ASSUME_NONNULL_END
