// Copyright 2013 Omni Development, Inc. All rights reserved.
//
// This software may only be used and reproduced according to the
// terms in the file OmniSourceLicense.html, which should be
// distributed with this project and can also be found at
// <http://www.omnigroup.com/developer/sourcecode/sourcelicense/>.

#import <OmniFileExchange/OFXErrors.h>

RCS_ID("$Id$")

// Can't use OMNI_BUNDLE_IDENTIFIER since this code might build in multiple bundles and we want our domain to remain distinct
NSString * const OFXErrorDomain = @"com.omnigroup.frameworks.OmniFileExchange.ErrorDomain";
