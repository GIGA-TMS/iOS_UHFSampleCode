//
//  TwoParameterAPICollectionViewCell.h
//  SampleGigatmsSDK
//
//  Created by Gianni on 2019/11/5.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface TwoParameterAPIViewCell : UIView
@property (strong, nonatomic) IBOutlet UIView *contentView;
@property (strong, nonatomic) IBOutlet UILabel *labTitle;
@property (strong, nonatomic) IBOutlet UIButton *btnRead;
@property (strong, nonatomic) IBOutlet UIButton *btnWrite;
@property (strong, nonatomic) IBOutlet UILabel *labDescription;
@property (strong, nonatomic) IBOutlet UILabel *labIstempDescription;
@property (strong, nonatomic) IBOutlet UISwitch *swIsTemp;
@property (strong, nonatomic) IBOutlet UITextField *txtParameter;

@end

NS_ASSUME_NONNULL_END
