//	Copyright (c) 2009 Stephen Deken
//	All rights reserved.
// 
//	Redistribution and use in source and binary forms, with or without modification,
//	are permitted provided that the following conditions are met:
//
//	*	Redistributions of source code must retain the above copyright notice, this
//		list of conditions and the following disclaimer.
//	*	Redistributions in binary form must reproduce the above copyright notice,
//		this list of conditions and the following disclaimer in the documentation
//		and/or other materials provided with the distribution.
//	*	Neither the name KeyCastr nor the names of its contributors may be used to
//		endorse or promote products derived from this software without specific
//		prior written permission.
//
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//	IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
//	INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
//	OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#import <Cocoa/Cocoa.h>
#import "KCVisualizer.h"

@interface KCDefaultVisualizerFactory : KCVisualizerFactory <KCVisualizerFactory>
{
}

-(NSString*) visualizerNibName;
-(Class) visualizerClass;
-(NSString*) visualizerName;

@end

@interface KCDefaultVisualizerBezelView : NSView
{
	double _maxWidth;
	NSColor* _foregroundColor;
	NSColor* _backgroundColor;
	double _fontSize;
	NSString* _contentText;
	BOOL _isCommand;
	float _opacity;

	NSTextStorage* _textStorage;
	NSLayoutManager* _layoutManager;
	NSTextContainer* _textContainer;
}

-(id) initWithMaxWidth:(double)maxWidth text:(NSString*)string isCommand:(BOOL)isCommand fontSize:(double)size fontColor:(NSColor*)fontColor backgroundColor:(NSColor*)color;
-(NSDictionary*) attributes;
-(void) maybeResize;
-(NSShadow*) shadow;
-(BOOL) isCommand;
-(void) setAlphaValue:(float)opacity;
-(void) appendString:(NSString*)t;
-(void) scheduleFadeOut;

@end

@class KCDefaultVisualizerWindow;

@interface KCBezelAnimation : NSAnimation
{
	KCDefaultVisualizerBezelView* _bezelView;
	NSWindow* _window;
}

-(KCBezelAnimation*) initWithBezelView:(KCDefaultVisualizerBezelView*)bezelView;
-(KCBezelAnimation*) initWithBezelView:(KCDefaultVisualizerBezelView*)bezelView window:(KCDefaultVisualizerWindow*)window;

@end

@interface KCDefaultVisualizerWindow : NSWindow
{
	NSMutableArray* _bezelViews;
	KCDefaultVisualizerBezelView* _mostRecentBezelView;
	NSMutableArray* _runningAnimations;
	BOOL _dragging;
}

-(void) addKeystroke:(KCKeystroke*)keystroke;
-(void) abandonCurrentView;
-(void) addRunningAnimation:(KCBezelAnimation*)animation;

@end

@interface KCDefaultVisualizer : KCVisualizer <KCVisualizer>
{
	KCDefaultVisualizerWindow* visualizerWindow;
}

-(NSString*) visualizerName;
-(void) deactivateVisualizer:(id)sender;

@end
