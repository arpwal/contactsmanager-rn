module.exports = {
  dependency: {
    platforms: {
      ios: {
        podspecPath: './ContactsmanagerRn.podspec',
        sharedLibraries: ['libc++'],
        frameworks: ['Contacts', 'ContactsUI'],
        scriptPhases: [
          {
            name: 'Configure ContactsManagerObjc Framework',
            path: './scripts/configure-framework-phase.sh',
            execution_position: 'after_compile',
          },
        ],
      },
      android: {
        sourceDir: './android',
        packageImportPath:
          'import com.contactsmanagerrn.ContactsmanagerRnPackage;',
        packageInstance: 'new ContactsmanagerRnPackage()',
      },
    },
  },
};
