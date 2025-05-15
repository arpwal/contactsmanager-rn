package com.contactsmanagerrn

import com.facebook.react.bridge.*
import io.contactsmanager.api.SocialService
import io.contactsmanager.api.models.CreateEventRequest
import io.contactsmanager.api.models.UpdateEventRequest
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext

class RNSocialService(private val reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext) {

    private val coroutineScope = CoroutineScope(Dispatchers.Main)

    override fun getName(): String {
        return "RNSocialService"
    }

    @ReactMethod
    fun followUser(userId: String, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.followUser(userId)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.followActionResponseToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("follow_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("follow_error", "Failed to follow user: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun unfollowUser(userId: String, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.unfollowUser(userId)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.followActionResponseToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("unfollow_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("unfollow_error", "Failed to unfollow user: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun isFollowingUser(userId: String, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.isFollowingUser(userId)
                }

                result.fold(
                    onSuccess = { response ->
                        val map = Arguments.createMap().apply {
                            putBoolean("isFollowing", response.isFollowing)
                        }
                        promise.resolve(map)
                    },
                    onFailure = { error ->
                        promise.reject("is_following_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("is_following_error", "Failed to check follow status: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getFollowers(userId: String, skip: Int, limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.getFollowers(if (userId.isEmpty()) null else userId, skip, limit)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.paginatedFollowListToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("get_followers_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("get_followers_error", "Failed to get followers: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getFollowing(userId: String, skip: Int, limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.getFollowing(if (userId.isEmpty()) null else userId, skip, limit)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.paginatedFollowListToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("get_following_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("get_following_error", "Failed to get following: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getMutualFollows(skip: Int, limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.getMutualFollows(skip, limit)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.paginatedMutualFollowersToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("get_mutual_follows_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("get_mutual_follows_error", "Failed to get mutual follows: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun createEvent(eventData: ReadableMap, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val createEventRequest = SocialConverter.readableMapToCreateEventRequest(eventData)
                val result = withContext(Dispatchers.IO) {
                    socialService.createEvent(createEventRequest)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.eventActionResponseToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("create_event_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("create_event_error", "Failed to create event: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getEvent(eventId: String, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.getEvent(eventId)
                }

                result.fold(
                    onSuccess = { event ->
                        promise.resolve(SocialConverter.socialEventToJS(event))
                    },
                    onFailure = { error ->
                        promise.reject("get_event_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("get_event_error", "Failed to get event: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun updateEvent(eventId: String, eventData: ReadableMap, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val updateEventRequest = SocialConverter.readableMapToUpdateEventRequest(eventData)
                val result = withContext(Dispatchers.IO) {
                    socialService.updateEvent(eventId, updateEventRequest)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.eventActionResponseToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("update_event_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("update_event_error", "Failed to update event: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun deleteEvent(eventId: String, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.deleteEvent(eventId)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.eventActionResponseToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("delete_event_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("delete_event_error", "Failed to delete event: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getUserEvents(userId: String, skip: Int, limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.getUserEvents(if (userId.isEmpty()) null else userId, skip, limit)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.paginatedEventListToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("get_user_events_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("get_user_events_error", "Failed to get user events: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getFeed(skip: Int, limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.getFeed(skip, limit)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.paginatedEventListToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("get_feed_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("get_feed_error", "Failed to get feed: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getUpcomingEvents(skip: Int, limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.getUpcomingEvents(skip, limit)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.paginatedEventListToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("get_upcoming_events_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("get_upcoming_events_error", "Failed to get upcoming events: ${e.message}", e)
            }
        }
    }

    @ReactMethod
    fun getForYouFeed(skip: Int, limit: Int, promise: Promise) {
        coroutineScope.launch {
            try {
                val socialService = SocialService.getInstance(reactContext)
                val result = withContext(Dispatchers.IO) {
                    socialService.getForYouFeed(skip, limit)
                }

                result.fold(
                    onSuccess = { response ->
                        promise.resolve(SocialConverter.paginatedEventListToJS(response))
                    },
                    onFailure = { error ->
                        promise.reject("get_for_you_feed_error", error.message, error)
                    }
                )
            } catch (e: Exception) {
                promise.reject("get_for_you_feed_error", "Failed to get for you feed: ${e.message}", e)
            }
        }
    }
}
