//
// ConvertPath.cpp : convert path from/to POSIX/HFS
//
//  base on HostedPluginExample.cpp
//  HostedPluginExample
//
//	This control plugin sample demonstrates how to expose an arbitrary NSView
//  from the plugin and forward events. For the example, a read-only rating level
//  indicator has been wrapped.
//
//  Copyright (c) 2013 Xojo Inc. All rights reserved.
//

#include "rb_plugin.h"

static REALstring PosixToHFS(REALstring posixPath);
static REALstring HFSToPosix(REALstring HFSPath);

static CFStringRef get_posix_path(CFStringRef p_hfs_path);
static CFStringRef get_hfs_path(CFStringRef p_posix_path);

REALmethodDefinition ConvertPathMethods[]={
    { (REALproc)PosixToHFS, REALnoImplementation, "PosixToHFS(posixPath as string) as string", REALconsoleSafe | REALScopeGlobal },
    { (REALproc)HFSToPosix, REALnoImplementation, "HFSToPosix(HFSPath as string) as string", REALconsoleSafe | REALScopeGlobal },
};

REALmoduleDefinition ConvertPathDefinition = {
	kCurrentREALControlVersion,
	"ConvertPath",
	ConvertPathMethods,
	sizeof( ConvertPathMethods ) / sizeof( REALmethodDefinition ),
	nil,  // ConvertPathConstants,                                      --> No Use
	nil,  // sizeof( ConvertPathConstants ) / sizeof( REALconstant ),   --> No Use
	nil,  // ConvertPathProperties,                                     --> No Use
	nil,  // sizeof( ConvertPathProperties ) / sizeof( REALproperty ),  --> No Use
};

//static REALstring CatString( REALstring str1, REALstring str2 ) {
//	NSString* nsstr1 = (NSString *)REALCopyStringCFString(str1);
//	NSString* nsstr2 = (NSString *)REALCopyStringCFString(str2);
//
//	NSString* nsstr3 = [NSString stringWithFormat:@"%@ %@",nsstr1, nsstr2];
//	const char* cstr3 = [nsstr3 UTF8String];
//
//	return REALBuildString(cstr3, ::strlen(cstr3));
//}

static REALstring PosixToHFS(REALstring posixPath)
{
    NSString *HFSPath=(NSString *)get_hfs_path(REALCopyStringCFString(posixPath));
	const char* cstr = [HFSPath UTF8String];
	
	return REALBuildString(cstr, ::strlen(cstr));
}

static REALstring HFSToPosix(REALstring HFSPath)
{
    NSString *posixPath=(NSString *)get_posix_path(REALCopyStringCFString(HFSPath));
//    CFStringRef aCFString = (CFStringRef)aNSString;
//    NSString *aNSString = (NSString *)aCFString;
	const char* cstr = [posixPath UTF8String];
	
	return REALBuildString(cstr, ::strlen(cstr));
}

CFStringRef get_posix_path (const CFStringRef p_hfs_path)
{
    CFURLRef	file_url;
    CFStringRef posix_path;
    
    // Get the url from a HFS path.
//    file_url = CFURLCreateWithFileSystemPath (
//                                              kCFAllocatorDefault,
//                                              p_hfs_path,
//                                             kCFURLHFSPathStyle, false);
    file_url = CFURLCreateWithFileSystemPath (NULL,p_hfs_path,
                                                 kCFURLHFSPathStyle, NO);
    
    // Get the posix path from the url.
    posix_path = CFURLCopyFileSystemPath (file_url,
                                          kCFURLPOSIXPathStyle);
    CFRelease (file_url);
    return posix_path;

//    NSString *posixPath=@"/Users/motohisa/Documents/chikaoka.pdf"; // assume this exists
//    NSString *hfsPath;
//    CFURLRef myURL = CFURLCreateWithFileSystemPath(NULL,
//                                                   (__bridge CFStringRef)posixPath, kCFURLPOSIXPathStyle, NO);
    
//    hfsPath = (__bridge NSString *)CFURLCopyFileSystemPath(myURL, kCFURLHFSPathStyle);
}

CFStringRef get_hfs_path (const CFStringRef p_posix_path)
{
    CFURLRef	file_url;
    CFStringRef hfs_path;
    
    // Get the url from a POSIX path.
    file_url = CFURLCreateWithFileSystemPath (
                                              kCFAllocatorDefault,
                                              p_posix_path,
                                              kCFURLPOSIXPathStyle, false);
    
    // Get the hfs path from the url.
    hfs_path = CFURLCopyFileSystemPath (file_url,
                                          kCFURLHFSPathStyle);
    CFRelease (file_url);
    return hfs_path;
}

void PluginEntry( void ) {
	REALRegisterModule( &ConvertPathDefinition );
}
