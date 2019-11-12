//
//  TwoParameterAPICollectionViewCell.m
//  SampleGigatmsSDK
//
//  Created by Gianni on 2019/11/5.
//  Copyright © 2019 Gianni. All rights reserved.
//

#import "TwoParameterAPIViewCell.h"

@implementation TwoParameterAPIViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}


- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self) {
//                [self customInit];
        
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self customInit];
    }
    return self;
}

-(void)customInit {
    
        UIView *xibView = [[[NSBundle mainBundle] loadNibNamed:@"TwoParameterAPIViewCell"
                                                         owner:self
                                                       options:nil]
                           objectAtIndex:0];
    //    xibView.frame = CGRectMake(0, 0, self.frame.size.width, self.frame.size.height);
        xibView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        [self addSubview: xibView];
    
    
}
@end
