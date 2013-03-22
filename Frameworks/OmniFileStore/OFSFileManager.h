// Copyright 2008-2013 Omni Development, Inc. All rights reserved.
//
// This software may only be used and reproduced according to the
// terms in the file OmniSourceLicense.html, which should be
// distributed with this project and can also be found at
// <http://www.omnigroup.com/developer/sourcecode/sourcelicense/>.
//
// $Id$

#import <Foundation/NSObject.h>

@protocol OFSAsynchronousOperation;

extern NSInteger OFSFileManagerDebug;

// intentionally similar to NSFileManager NSDirectoryEnumerationOptions
enum {
    OFSDirectoryEnumerationSkipsSubdirectoryDescendants = 1UL << 0,     /* shallow, non-deep */
    /* OFSDirectoryEnumerationSkipsPackageDescendants = 1UL << 1, */    /* no package contents, not currently supported */
    OFSDirectoryEnumerationSkipsHiddenFiles = 1UL << 2,                 /* no hidden files */
    OFSDirectoryEnumerationForceRecursiveDirectoryRead = 1UL << 3,       /* useful when the server does not implement PROPFIND requests with Depth:infinity */
};
typedef NSUInteger OFSDirectoryEnumerationOptions;


@protocol OFSFileManagerDelegate;

@interface OFSFileManager : NSObject

+ (Class)fileManagerClassForURLScheme:(NSString *)scheme;

- initWithBaseURL:(NSURL *)baseURL delegate:(id <OFSFileManagerDelegate>)delegate error:(NSError **)outError;

@property(nonatomic,readonly) NSURL *baseURL;
@property(nonatomic,weak,readonly) id <OFSFileManagerDelegate> delegate;

- (void)invalidate;

- (id <OFSAsynchronousOperation>)asynchronousReadContentsOfURL:(NSURL *)url;
- (id <OFSAsynchronousOperation>)asynchronousWriteData:(NSData *)data toURL:(NSURL *)url atomically:(BOOL)atomically;

- (NSURL *)availableURL:(NSURL *)startingURL;

- (NSURL *)createDirectoryAtURLIfNeeded:(NSURL *)directoryURL error:(NSError **)outError;

@end

@class OFSFileInfo;

@protocol OFSConcreteFileManager

+ (BOOL)shouldHaveHostInURL;

// Returns an OFSFileInfo. If we determine that the file does not exist, returns an OFSFileInfo with exists=NO.
- (OFSFileInfo *)fileInfoAtURL:(NSURL *)url error:(NSError **)outError;

// For the following methods, a few underlying scheme-specific errors are translated/wrapped into XMLData error codes for consistency:
//   Directory operation on nonexistent directory  -->  OFSNoSuchDirectory
// 

// Returns an array of OFSFileInfos for the immediate children of the given URL.  The results are in no particular order.
// Returns nil and sets *outError if the URL does not refer to a directory/folder/collection (among other possible reasons).
- (NSArray *)directoryContentsAtURL:(NSURL *)url havingExtension:(NSString *)extension options:(OFSDirectoryEnumerationOptions)options error:(NSError **)outError;
- (NSArray *)directoryContentsAtURL:(NSURL *)url havingExtension:(NSString *)extension error:(NSError **)outError;  // passes OFSDirectoryEnumerationSkipsSubdirectoryDescendants for option

// Only published since OmniFocus was using this method on a generic OFSFileManager (for test cases that run vs. file: URLs). Once we switch that to always using DAV, this could go away
- (NSMutableArray *)directoryContentsAtURL:(NSURL *)url collectingRedirects:(NSMutableArray *)redirections options:(OFSDirectoryEnumerationOptions)options error:(NSError **)outError;

- (NSData *)dataWithContentsOfURL:(NSURL *)url error:(NSError **)outError;

- (NSURL *)writeData:(NSData *)data toURL:(NSURL *)url atomically:(BOOL)atomically error:(NSError **)outError;

- (NSURL *)createDirectoryAtURL:(NSURL *)url attributes:(NSDictionary *)attributes error:(NSError **)outError;

- (NSURL *)moveURL:(NSURL *)sourceURL toURL:(NSURL *)destURL error:(NSError **)outError;

// Failure due to the URL not existing will be mapped to OFSNoSuchFile (with an underlying Cocoa/POSIX or HTTP error).
- (BOOL)deleteURL:(NSURL *)url error:(NSError **)outError;

@end

// Any file mananger returned from -initWithBaseURL:error: will be concrete, so just fake up a declaration that they all are
@interface OFSFileManager (OFSConcreteFileManager) <OFSConcreteFileManager>
@end

extern void OFSFileManagerSplitNameAndCounter(NSString *originalName, NSString **outName, NSUInteger *outCounter); // just calls -[NSString splitName:andCounter:]

