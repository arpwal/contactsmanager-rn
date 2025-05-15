package com.contactsmanagerrn

import com.facebook.react.bridge.*
import io.contactsmanager.api.ContactService
import io.contactsmanager.api.models.CMContactFieldType
import io.contactsmanager.api.models.CMContactsManagerOptions
import io.contactsmanager.api.models.CMUserInfo
import io.contactsmanager.api.models.CMContactDataRestriction
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class RNContactService(private val reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    private val coroutineScope = CoroutineScope(Dispatchers.Main)

    override fun getName(): String {
        return "RNContactService"
    }

    @ReactMethod
    fun initialize(apiKey: String, userInfo: ReadableMap, token: String?, options: ReadableMap, promise: Promise) {
        coroutineScope.launch {
            try {
                val contactService = ContactService.getInstance(reactContext)

                val cmUserInfo = readableMapToUserInfo(userInfo)
                val cmOptions = readableMapToOptions(options)

                // Handle null token (empty string from JS is treated as null)
                val tokenToUse = if (token.isNullOrEmpty()) null else token

                val result = withContext(Dispatchers.IO) {
                    contactService.initialize(apiKey, tokenToUse, cmUserInfo, cmOptions)
                }

                result.fold(
                    onSuccess = { success ->
                        val response = Arguments.createMap().apply {
                            putBoolean("success", success)
                        }
                        promise.resolve(response)
                    },
                    onFailure = { error ->
                        promise.reject("init_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("init_error", "Failed to initialize contact service: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun isInitialized(promise: Promise) {
        try {
            val contactService = ContactService.getInstance(reactContext)
            val initialized = contactService.isInitialized()
            promise.resolve(initialized)
        } catch (e: Exception) {
            promise.reject("check_init_error", "Failed to check initialization status: ${e.message}", e)
        }
    }

    @ReactMethod
    fun currentState(promise: Promise) {
        try {
            val contactService = ContactService.getInstance(reactContext)
            val state = if (contactService.isInitialized()) "INITIALIZED" else "NOT_INITIALIZED"
            promise.resolve(state)
        } catch (e: Exception) {
            promise.reject("state_error", "Failed to get current state: ${e.message}", e)
        }
    }

    @ReactMethod
    fun reset(promise: Promise) {
        try {
            val contactService = ContactService.getInstance(reactContext)
            val result = contactService.reset()

            result.fold(
                onSuccess = { success ->
                    val response = Arguments.createMap().apply {
                        putBoolean("success", success)
                    }
                    promise.resolve(response)
                },
                onFailure = { error ->
                    promise.reject("reset_error", error.message, error)
                }
            )
        } catch (e: Exception) {
            promise.reject("reset_error", "Failed to reset contact service: ${e.message}", e)
        }
    }

    @ReactMethod
    fun requestContactsAccess(promise: Promise) {
        // This is handled by RNContactsAuthorizationService
        val response = Arguments.createMap().apply {
            putBoolean("granted", false)
            putString("error", "Use ContactsAuthorizationService.requestContactsAccess() instead")
        }
        promise.resolve(response)
    }

    @ReactMethod
    fun contactsAccessStatus(promise: Promise) {
        // This is handled by RNContactsAuthorizationService
        promise.resolve(0) // NOT_DETERMINED
    }

    @ReactMethod
    fun fetchContacts(promise: Promise) {
        coroutineScope.launch {
            try {
                val contactService = ContactService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    contactService.fetchContacts()
                }

                result.fold(
                    onSuccess = { contacts ->
                        promise.resolve(ContactsConverter.toJSArray(contacts))
                    },
                    onFailure = { error ->
                        promise.reject("fetch_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("fetch_error", "Failed to fetch contacts: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun fetchContactsWithFieldType(fieldType: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val contactService = ContactService.getInstance(reactContext)
                val cmFieldType = when (fieldType) {
                    0 -> CMContactFieldType.ANY
                    1 -> CMContactFieldType.PHONE
                    2 -> CMContactFieldType.EMAIL
                    3 -> CMContactFieldType.NOTES
                    else -> CMContactFieldType.ANY
                }

                val result = withContext(Dispatchers.IO) {
                    contactService.fetchContacts(cmFieldType)
                }

                result.fold(
                    onSuccess = { contacts ->
                        promise.resolve(ContactsConverter.toJSArray(contacts))
                    },
                    onFailure = { error ->
                        promise.reject("fetch_field_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("fetch_field_error", "Failed to fetch contacts with field type: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun fetchContactsWithBatch(batchSize: Int, batchIndex: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val contactService = ContactService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    contactService.fetchContacts(batchSize, batchIndex)
                }

                result.fold(
                    onSuccess = { contacts ->
                        promise.resolve(ContactsConverter.toJSArray(contacts))
                    },
                    onFailure = { error ->
                        promise.reject("fetch_batch_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("fetch_batch_error", "Failed to fetch contacts with batch: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun fetchContactWithId(contactId: String, promise: Promise) {
        coroutineScope.launch {
            try {
                val contactService = ContactService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    contactService.fetchContact(contactId)
                }

                result.fold(
                    onSuccess = { contact ->
                        if (contact != null) {
                            promise.resolve(ContactsConverter.toJS(contact))
                        } else {
                            promise.reject("contact_not_found", "Contact not found with ID: $contactId")
                        }
                    },
                    onFailure = { error ->
                        promise.reject("fetch_contact_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("fetch_contact_error", "Failed to fetch contact: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getContactsCount(promise: Promise) {
        coroutineScope.launch {
            try {
                val contactService = ContactService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    contactService.getContactsCount()
                }

                result.fold(
                    onSuccess = { count ->
                        promise.resolve(count)
                    },
                    onFailure = { error ->
                        promise.reject("count_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("count_error", "Failed to get contacts count: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun enableBackgroundSync(promise: Promise) {
        // Not directly supported in Android, would need custom implementation
        promise.resolve(false)
    }

    @ReactMethod
    fun scheduleBackgroundSyncTask(promise: Promise) {
        // Not directly supported in Android, would need custom implementation
        promise.resolve(false)
    }

    @ReactMethod
    fun checkHealth(promise: Promise) {
        try {
            val contactService = ContactService.getInstance(reactContext)
            val isHealthy = contactService.isInitialized()
            val response = Arguments.createMap().apply {
                putBoolean("healthy", isHealthy)
            }
            promise.resolve(response)
        } catch (e: Exception) {
            val response = Arguments.createMap().apply {
                putBoolean("healthy", false)
            }
            promise.resolve(response)
        }
    }

    @ReactMethod
    fun hasContactChanged(contact: ReadableMap, promise: Promise) {
        // Not directly supported in Android, would need custom implementation
        promise.resolve(false)
    }

    @ReactMethod
    fun getContactsForSync(promise: Promise) {
        coroutineScope.launch {
            try {
                val contactService = ContactService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    contactService.fetchContacts()
                }

                result.fold(
                    onSuccess = { contacts ->
                        // Filter contacts that need sync (simplified implementation)
                        promise.resolve(ContactsConverter.toJSArray(contacts))
                    },
                    onFailure = { error ->
                        promise.reject("sync_contacts_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("sync_contacts_error", "Failed to get contacts for sync: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun startSync(sourceId: String, userId: String, promise: Promise) {
        coroutineScope.launch {
            try {
                val contactService = ContactService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    contactService.syncContacts()
                }

                result.fold(
                    onSuccess = { success ->
                        val response = Arguments.createMap().apply {
                            putInt("syncedCount", 0) // Simplified implementation
                        }
                        promise.resolve(response)
                    },
                    onFailure = { error ->
                        promise.reject("sync_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("sync_error", "Failed to start sync: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun cancelSync(promise: Promise) {
        // Not directly supported in Android, would need custom implementation
        promise.resolve(true)
    }

    // Helper methods for converting between JS and native objects

    private fun readableMapToUserInfo(userInfo: ReadableMap): CMUserInfo {
        return CMUserInfo(
            userId = userInfo.getString("userId") ?: throw IllegalArgumentException("userId is required"),
            fullName = if (userInfo.hasKey("fullName")) userInfo.getString("fullName") else null,
            email = if (userInfo.hasKey("email")) userInfo.getString("email") else null,
            phone = if (userInfo.hasKey("phone")) userInfo.getString("phone") else null,
            avatarUrl = if (userInfo.hasKey("avatarUrl")) userInfo.getString("avatarUrl") else null,
            metadata = if (userInfo.hasKey("metadata")) {
                val metadataMap = userInfo.getMap("metadata")
                metadataMap?.toHashMap()?.mapValues { it.value.toString() }
            } else null
        )
    }

    private fun readableMapToOptions(options: ReadableMap): CMContactsManagerOptions {
        val optionsBuilder = CMContactsManagerOptions.Builder()

        if (options.hasKey("dataRestrictions")) {
            val restrictionsArray = options.getArray("dataRestrictions")
            val restrictions = mutableSetOf<CMContactDataRestriction>()

            restrictionsArray?.let {
                for (i in 0 until it.size()) {
                    when (it.getString(i)?.uppercase()) {
                        "NOTES" -> restrictions.add(CMContactDataRestriction.NOTES)
                    }
                }
            }

            optionsBuilder.setDataRestrictions(restrictions)
        }

        if (options.hasKey("shouldSyncDeletedContacts")) {
            optionsBuilder.setShouldSyncDeletedContacts(options.getBoolean("shouldSyncDeletedContacts"))
        }

        if (options.hasKey("shouldSyncContactImages")) {
            optionsBuilder.setShouldSyncContactImages(options.getBoolean("shouldSyncContactImages"))
        }

        if (options.hasKey("shouldSyncContactThumbnails")) {
            optionsBuilder.setShouldSyncContactThumbnails(options.getBoolean("shouldSyncContactThumbnails"))
        }

        return optionsBuilder.build()
    }
}
