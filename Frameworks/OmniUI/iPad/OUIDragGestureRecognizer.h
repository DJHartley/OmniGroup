// Copyright 2010-2011 The Omni Group.  All rights reserved.
//
// This software may only be used and reproduced according to the
// terms in the file OmniSourceLicense.html, which should be
// distributed with this project and can also be found at
// <http://www.omnigroup.com/developer/sourcecode/sourcelicense/>.
//
// $Id$

#import <UIKit/UIGestureRecognizerSubclass.h>
#import "OUIGestureRecognizer.h"

@interface OUIDragGestureRecognizer : OUIGestureRecognizer
{
@private
    CGFloat hysteresisDistance;
    BOOL overcameHysteresis;
    
    // Points stored in window coordinates
    CGPoint firstTouchPoint;
    CGPoint latestTouchPoint;
    
    BOOL wasATap;
}

// Settings
@property (nonatomic) CGFloat hysteresisDistance;

// Actions
- (void)resetHysteresis;

// Properties
@property (readonly, nonatomic) BOOL wasATap;  // YES if the gesture is ending without overcoming hysteresis.
@property (readonly, nonatomic) BOOL touchIsDown;
@property (readonly, nonatomic) BOOL overcameHysteresis;

- (CGPoint)touchBeganPoint;  // TODO: Remove (it's here for compatibility with GPMoveGestureRecognizer
- (CGPoint)firstTouchPointInView:(UIView *)view;
- (CGPoint)cumulativeOffsetInView:(UIView *)view;

@end