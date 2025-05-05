#import "ContactsmanagerRn.h"

@implementation ContactsmanagerRn

RCT_EXPORT_MODULE()

// Main module now just serves as an umbrella module
// All functionality has been moved to dedicated modules:
// - RNContactsAuthorizationService: handles contacts permissions
// - RNContactsManager: handles contacts data retrieval

@end
