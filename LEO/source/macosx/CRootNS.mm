#include "CRootNS.h"

//
namespace Leo{
  
  CRootNS::CRootNS()
  {
    // Initialize NSApp
    NSApplication* app = [NSApplication sharedApplication];
    
    // Set App Delegate
    [app setDelegate:[[LeoAppDelegate alloc] initWithRoot:this]];
    
  }
  
  CRootNS::~CRootNS()
  {
  }
  
  void CRootNS::run(void)
  {
    [NSApp run];
  }
  
}

///////////////////////////////////////////////////////////////////

@implementation LeoAppDelegate

//
- (id)initWithRoot:(Leo::CRootNS*)instance
{
  self = [super init];
  if(self)
  {
    m_RootInstance = instance;
  }
  return self;
}

@end

///////////////////////////////////////////////////////////////////

@implementation LeoAppDelegate (EventResponder)

//
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
  // Get Running Application
  NSRunningApplication* rapp = [NSRunningApplication currentApplication];
  
  // Create Main Menu
  {
    NSMenu* menu = [[NSMenu alloc] initWithTitle:[rapp localizedName]];
    NSMenu* submenu;
    NSMenuItem* item;
    
    item = [menu addItemWithTitle:@"Apple" action:NULL keyEquivalent:@""];
    submenu = [[NSMenu alloc] initWithTitle:@"Apple"];
    [menu setSubmenu:submenu forItem:item];
    [submenu release];
    
    item = [submenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@",
                                      NSLocalizedString(@"Quit", nil), 
                                      [rapp localizedName]]
                              action:@selector(terminate:)
                       keyEquivalent:@"q"];
    [item setTarget:NSApp];
    
    [NSApp setMainMenu:menu];
    [menu release];
  }
  
  
}

//
- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
}

//
- (void)applicationWillTerminate:(NSNotification*)aNotification
{
}

@end

///////////////////////////////////////////////////////////////////

@implementation LeoAppDelegate (Properties)

//
- (NSApplicationTerminateReply)
applicationShouldTerminate:(NSApplication*)sender
{
  return NSTerminateNow;
}

//
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:
(NSApplication *)theApplication
{
  return YES;
}

@end

