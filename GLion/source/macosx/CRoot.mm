#import <Cocoa/Cocoa.h>
#include "CRoot.h"
#include <cstdlib>

/////////////////////////////////////////////////////////////////

@interface GLionAppDelegate : NSObject<NSApplicationDelegate>
{
  NSString* m_Title;
  NSTimer* m_RenderTimer;
}

- (id)initWithTitle:(NSString*)title;

@end

@implementation GLionAppDelegate

- (id)initWithTitle:(NSString*)title
{
  self = [super init];
  
  if(self){
    m_Title = [title retain];
  }
  
  return self;
}

- (void)dealloc
{
  [m_Title release];
  [super dealloc];
}

- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
  // Create Main Menu
  {
    //
    NSMenu* menu = [[NSMenu alloc] initWithTitle:m_Title];
    NSMenu* submenu;
    NSMenuItem* item;
    
    //
    item = [menu addItemWithTitle:@"Apple" action:NULL keyEquivalent:@""];
    submenu = [[NSMenu alloc] initWithTitle:@"Apple"];
    [menu setSubmenu:[submenu autorelease] forItem:item];
    
    {
      item = [submenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@",
                                        NSLocalizedString(@"Quit", nil), 
                                        m_Title]
                                action:@selector(terminate:)
                         keyEquivalent:@"q"];
      [item setTarget:NSApp];
    }
    
    //
    [NSApp setMainMenu:[menu autorelease]];
    
    //
    [NSMenu setMenuBarVisible:YES];
  }
  
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
  // Create NSOpenGLView
  {
    
  }
  
  // Create Render Timer
  m_RenderTimer = 
  [NSTimer scheduledTimerWithTimeInterval:0.0
                                   target:[NSApp delegate]
                                 selector:@selector(_kickOneFrame:)
                                 userInfo:nil
                                  repeats:YES];
  
  //
  
  
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:
(NSApplication *)theApplication
{
  return YES;
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
  // Stop & Remove Render Timer
  [m_RenderTimer invalidate];
}

- (NSApplicationTerminateReply)
applicationShouldTerminate:(NSApplication*)sender
{
  return NSTerminateNow;
}

- (void)_kickOneFrame:(NSTimer*)sender
{
  //
  GLion::CRoot::inst()->_kickOneFrame();
}

@end

/////////////////////////////////////////////////////////////////

namespace GLion{
  
  CRoot::CRoot()
  {
    // New Autorelease Pool
    m_Pool = [[NSAutoreleasePool alloc] init];
    
    // Initialize NSApp
    [NSApplication sharedApplication];
  }
  
  CRoot::~CRoot()
  {
    // Release Autorelease Pool
    [m_Pool drain];
    //[m_Pool release];
  }
  
  bool CRoot::initialize(const CStringParam& title)
  {
    // Set Delegate
    {
      NSString* nstitle = [NSString stringWithUTF8String:title.get()];
      [NSApp setDelegate:[[GLionAppDelegate alloc] initWithTitle:nstitle]];
    }
    
    // Initial
    
    return true;
  }
  
  bool CRoot::run(void)
  {
    [NSApp run];
    
    return true;
  }
  
  
}

/////////////////////////////////////////////////////////////////

namespace GLion{
  
  void CRoot::_kickOneFrame()
  {
    NSLog(@"Render One Frame");
  }
  
  void CRoot::_initSystem()
  {
    
  }
  
  void CRoot::_destroySystem()
  {
  }
  
}

/////////////////////////////////////////////////////////////////

namespace GLion{
  
  CRoot CRoot::sm_Instance;
  
  IRoot& IRoot::instance()
  {
    return CRoot::sm_Instance;
  }
  
}

