//  Copyright © 2016 Scott Talbot. All rights reserved.

#import <Foundation/Foundation.h>


FOUNDATION_EXPORT double STEventSourceVersionNumber;
FOUNDATION_EXPORT const unsigned char STEventSourceVersionString[];


NS_ASSUME_NONNULL_BEGIN


extern NSString * const STEventSourceErrorDomain;

typedef NS_ENUM(NSUInteger, STEventSourceErrorCode) {
    STEventSourceUnknownError = 0,
    STEventSourceInvalidOperationError,
    STEventSourceResourceNotFoundError,
    STEventSourceIncorrectResponseContentTypeError,
};


typedef NS_ENUM(NSUInteger, STEventSourceReadyState) {
    STEventSourceReadyStateClosed = 0,
    STEventSourceReadyStateConnecting,
    STEventSourceReadyStateOpen,
};


@protocol STEventSourceEvent <NSObject>
@property (nonatomic,copy,nullable,readonly) NSString *type;
@property (nonatomic,copy,readonly) NSString *data;
@end


typedef void(^STEventSourceEventHandler)(id<STEventSourceEvent> event);
typedef void(^STEventSourceCompletionHandler)(NSError * __nullable error);


@interface STEventSource : NSObject

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithURL:(NSURL *)url handler:(STEventSourceEventHandler)handler completion:(STEventSourceCompletionHandler)completion;
- (instancetype)initWithURL:(NSURL *)url httpHeaders:(NSDictionary<NSString *, NSString *> * __nullable)httpHeaders handler:(STEventSourceEventHandler)handler completion:(STEventSourceCompletionHandler)completion;
- (instancetype)initWithSessionConfiguration:(NSURLSessionConfiguration * __nullable)sessionConfiguration url:(NSURL *)url handler:(STEventSourceEventHandler)handler completion:(STEventSourceCompletionHandler)completion;
- (instancetype)initWithSessionConfiguration:(NSURLSessionConfiguration * __nullable)sessionConfiguration url:(NSURL *)url httpHeaders:(NSDictionary<NSString *, NSString *> * __nullable)httpHeaders handler:(STEventSourceEventHandler)handler completion:(STEventSourceCompletionHandler)completion NS_DESIGNATED_INITIALIZER;

@property (nonatomic,strong,readonly) NSURLSessionConfiguration *sessionConfiguration;

@property (nonatomic,assign,readonly) STEventSourceReadyState readyState;

- (void)open NS_SWIFT_UNAVAILABLE("");
- (BOOL)openWithError:(NSError * __nullable __autoreleasing * __nullable)error;

- (void)close NS_SWIFT_UNAVAILABLE("");
- (BOOL)closeWithError:(NSError * __nullable __autoreleasing * __nullable)error;

@property (nonatomic,copy,nullable,readonly) NSString *lastEventId;

@property (nonatomic,assign,readonly) NSTimeInterval retryInterval;

@end


NS_ASSUME_NONNULL_END
