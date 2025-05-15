package com.contactsmanagerrn

import com.facebook.react.bridge.*
import io.contactsmanager.api.ContactSearchService
import io.contactsmanager.api.SearchFieldType
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class RNContactSearchService(private val reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    private val coroutineScope = CoroutineScope(Dispatchers.Main)

    override fun getName(): String {
        return "RNContactSearchService"
    }

    @ReactMethod
    fun searchContacts(query: String, fieldType: Int, offset: Int, limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val searchService = ContactSearchService.getInstance(reactContext)
                val searchFieldType = when (fieldType) {
                    1 -> SearchFieldType.NAME
                    2 -> SearchFieldType.EMAIL
                    4 -> SearchFieldType.PHONE
                    8 -> SearchFieldType.ADDRESS
                    16 -> SearchFieldType.ORGANIZATION
                    32 -> SearchFieldType.NOTES
                    else -> SearchFieldType.ALL
                }

                val result = withContext(Dispatchers.IO) {
                    searchService.searchContacts(query, searchFieldType, offset, limit)
                }

                result.fold(
                    onSuccess = { searchResult ->
                        val response = Arguments.createMap().apply {
                            putArray("contacts", ContactsConverter.toJSArray(searchResult.contacts))
                            putInt("totalCount", searchResult.totalCount)
                        }
                        promise.resolve(response)
                    },
                    onFailure = { error ->
                        promise.reject("search_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("search_error", "Failed to search contacts: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun quickSearch(query: String, promise: Promise) {
        coroutineScope.launch {
            try {
                val searchService = ContactSearchService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    searchService.quickSearch(query)
                }

                result.fold(
                    onSuccess = { contacts ->
                        promise.resolve(ContactsConverter.toJSArray(contacts))
                    },
                    onFailure = { error ->
                        promise.reject("quick_search_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("quick_search_error", "Failed to quick search contacts: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getContactsCount(promise: Promise) {
        coroutineScope.launch {
            try {
                val searchService = ContactSearchService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    searchService.getContactsCount()
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
}
