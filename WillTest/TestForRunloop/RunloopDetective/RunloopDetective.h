//
//  RunloopDetective.h
//  TestForRunloop
//
//  Created by meitu007 on 2020/2/25.
//  Copyright © 2020 meitu. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RunloopDetective : NSObject

+ (instancetype)sharedInstance;

- (void)start;

- (void)stop;

@end

NS_ASSUME_NONNULL_END
