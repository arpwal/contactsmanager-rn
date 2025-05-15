package com.contactsmanagerrn

import com.facebook.react.bridge.*
import io.contactsmanager.api.models.*

/**
 * Utility class for converting between native social objects and JS objects
 */
object SocialConverter {

    /**
     * Convert a FollowActionResponse to a WritableMap for JS
     */
    fun followActionResponseToJS(response: FollowActionResponse): WritableMap {
        return Arguments.createMap().apply {
            putBoolean("success", response.success)
            putString("message", response.message)
            putString("userId", response.userId)
            putBoolean("isFollowing", response.isFollowing)
        }
    }

    /**
     * Convert a PaginatedFollowList to a WritableMap for JS
     */
    fun paginatedFollowListToJS(list: PaginatedFollowList): WritableMap {
        return Arguments.createMap().apply {
            putArray("items", canonicalContactsToJSArray(list.items))
            putInt("total", list.total)
            putInt("skip", list.skip)
            putInt("limit", list.limit)
        }
    }

    /**
     * Convert a PaginatedMutualFollowers to a WritableMap for JS
     */
    fun paginatedMutualFollowersToJS(list: PaginatedMutualFollowers): WritableMap {
        return Arguments.createMap().apply {
            putArray("items", canonicalContactsToJSArray(list.items))
            putInt("total", list.total)
            putInt("skip", list.skip)
            putInt("limit", list.limit)
        }
    }

    /**
     * Convert a EventActionResponse to a WritableMap for JS
     */
    fun eventActionResponseToJS(response: EventActionResponse): WritableMap {
        return Arguments.createMap().apply {
            putBoolean("success", response.success)
            putString("message", response.message)
            putString("eventId", response.eventId)
        }
    }

    /**
     * Convert a SocialEvent to a WritableMap for JS
     */
    fun socialEventToJS(event: SocialEvent): WritableMap {
        return Arguments.createMap().apply {
            putString("id", event.id)
            putString("title", event.title)
            putString("description", event.description)
            putString("location", event.location)
            putString("imageUrl", event.imageUrl)
            putDouble("startTime", event.startTime?.toDouble() ?: 0.0)
            putDouble("endTime", event.endTime?.toDouble() ?: 0.0)
            putString("creatorId", event.creatorId)
            putMap("creator", event.creator?.let { canonicalContactToJS(it) } ?: Arguments.createMap())
            putArray("attendees", event.attendees?.let { canonicalContactsToJSArray(it) } ?: Arguments.createArray())
            putInt("attendeeCount", event.attendeeCount ?: 0)
            putString("status", event.status)
            putDouble("createdAt", event.createdAt?.toDouble() ?: 0.0)
            putDouble("updatedAt", event.updatedAt?.toDouble() ?: 0.0)
        }
    }

    /**
     * Convert a PaginatedEventList to a WritableMap for JS
     */
    fun paginatedEventListToJS(list: PaginatedEventList): WritableMap {
        return Arguments.createMap().apply {
            putArray("items", socialEventsToJSArray(list.items))
            putInt("total", list.total)
            putInt("skip", list.skip)
            putInt("limit", list.limit)
        }
    }

    /**
     * Convert a list of SocialEvent objects to a WritableArray for JS
     */
    fun socialEventsToJSArray(events: List<SocialEvent>): WritableArray {
        val array = Arguments.createArray()
        events.forEach { event ->
            array.pushMap(socialEventToJS(event))
        }
        return array
    }

    /**
     * Convert a list of CanonicalContact objects to a WritableArray for JS
     */
    fun canonicalContactsToJSArray(contacts: List<CanonicalContact>): WritableArray {
        val array = Arguments.createArray()
        contacts.forEach { contact ->
            array.pushMap(canonicalContactToJS(contact))
        }
        return array
    }

    /**
     * Convert a CanonicalContact to a WritableMap for JS
     */
    fun canonicalContactToJS(contact: CanonicalContact): WritableMap {
        return Arguments.createMap().apply {
            putString("id", contact.id)
            putString("userId", contact.userId)
            putString("displayName", contact.displayName)
            putString("givenName", contact.givenName)
            putString("familyName", contact.familyName)
            putString("username", contact.username)
            putString("avatarUrl", contact.avatarUrl)
            putString("bio", contact.bio)
            putDouble("createdAt", contact.createdAt?.toDouble() ?: 0.0)
            putDouble("updatedAt", contact.updatedAt?.toDouble() ?: 0.0)
        }
    }

    /**
     * Convert a ReadableMap to CreateEventRequest
     */
    fun readableMapToCreateEventRequest(map: ReadableMap): CreateEventRequest {
        return CreateEventRequest(
            title = map.getString("title") ?: "",
            description = map.getString("description"),
            location = map.getString("location"),
            imageUrl = map.getString("imageUrl"),
            startTime = if (map.hasKey("startTime")) map.getDouble("startTime").toLong() else null,
            endTime = if (map.hasKey("endTime")) map.getDouble("endTime").toLong() else null,
            status = map.getString("status")
        )
    }

    /**
     * Convert a ReadableMap to UpdateEventRequest
     */
    fun readableMapToUpdateEventRequest(map: ReadableMap): UpdateEventRequest {
        return UpdateEventRequest(
            title = if (map.hasKey("title")) map.getString("title") else null,
            description = if (map.hasKey("description")) map.getString("description") else null,
            location = if (map.hasKey("location")) map.getString("location") else null,
            imageUrl = if (map.hasKey("imageUrl")) map.getString("imageUrl") else null,
            startTime = if (map.hasKey("startTime")) map.getDouble("startTime").toLong() else null,
            endTime = if (map.hasKey("endTime")) map.getDouble("endTime").toLong() else null,
            status = if (map.hasKey("status")) map.getString("status") else null
        )
    }
}
