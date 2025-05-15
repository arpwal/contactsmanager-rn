package com.contactsmanagerrn

import com.facebook.react.bridge.*
import io.contactsmanager.api.RecommendationService
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class RNRecommendationService(private val reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    private val coroutineScope = CoroutineScope(Dispatchers.Main)

    override fun getName(): String {
        return "RNRecommendationService"
    }

    @ReactMethod
    fun getInviteRecommendations(limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val recommendationService = RecommendationService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    recommendationService.getSharedContactsByUsersToInvite(limit)
                }

                result.fold(
                    onSuccess = { recommendations ->
                        promise.resolve(ContactsConverter.recommendationsToJSArray(recommendations))
                    },
                    onFailure = { error ->
                        promise.reject("recommendation_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("recommendation_error", "Failed to get invite recommendations: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getContactsUsingApp(limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val recommendationService = RecommendationService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    recommendationService.getContactsUsingApp(limit)
                }

                result.fold(
                    onSuccess = { contacts ->
                        promise.resolve(ContactsConverter.localCanonicalContactsToJSArray(contacts))
                    },
                    onFailure = { error ->
                        promise.reject("contacts_using_app_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("contacts_using_app_error", "Failed to get contacts using app: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getUsersYouMightKnow(limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val recommendationService = RecommendationService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    recommendationService.getUsersYouMightKnow(limit)
                }

                result.fold(
                    onSuccess = { users ->
                        promise.resolve(ContactsConverter.canonicalContactsToJSArray(users))
                    },
                    onFailure = { error ->
                        promise.reject("users_you_might_know_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("users_you_might_know_error", "Failed to get users you might know: ${e.message}", e)
            }
        }
    }
}
