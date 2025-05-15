package com.contactsmanagerrn

import com.facebook.react.bridge.Arguments
import com.facebook.react.bridge.ReadableMap
import com.facebook.react.bridge.WritableArray
import com.facebook.react.bridge.WritableMap
import io.contactsmanager.api.models.*
import java.util.*

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
     * Convert a FollowStatusResponse to a WritableMap for JS
     */
    fun followStatusResponseToJS(response: FollowStatusResponse): WritableMap {
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
    fun paginatedFollowListToJS(response: PaginatedFollowList): WritableMap {
        return Arguments.createMap().apply {
            putArray("items", followRelationshipsToJSArray(response.items))
            putInt("total", response.total)
            putInt("skip", response.skip)
            putInt("limit", response.limit)
        }
    }

    /**
     * Convert a list of FollowRelationship objects to a WritableArray for JS
     */
    fun followRelationshipsToJSArray(relationships: List<FollowRelationship>): WritableArray {
        val array = Arguments.createArray()
        relationships.forEach { relationship ->
            array.pushMap(followRelationshipToJS(relationship))
        }
        return array
    }

    /**
     * Convert a FollowRelationship to a WritableMap for JS
     */
    fun followRelationshipToJS(relationship: FollowRelationship): WritableMap {
        return Arguments.createMap().apply {
            putString("id", relationship.id)
            putString("userId", relationship.userId)
            putString("followerId", relationship.followerId)
            putMap("follower", relationship.follower?.let { canonicalContactToJS(it) })
            putMap("following", relationship.following?.let { canonicalContactToJS(it) })
            putDouble("createdAt", relationship.createdAt?.time?.toDouble() ?: 0.0)
            putDouble("updatedAt", relationship.updatedAt?.time?.toDouble() ?: 0.0)
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
            putString("imageUrl", event.imageUrl)
            putDouble("startTime", event.startTime?.time?.toDouble() ?: 0.0)
            putDouble("endTime", event.endTime?.time?.toDouble() ?: 0.0)
            putString("creatorId", event.creatorId)
            putMap("creator", event.creator?.let { canonicalContactToJS(it) })
            putArray("attendees", event.attendees?.let { canonicalContactsToJSArray(it) })
            putInt("attendeeCount", event.attendeeCount)
            putString("status", event.status?.name)
            putDouble("createdAt", event.createdAt?.time?.toDouble() ?: 0.0)
            putDouble("updatedAt", event.updatedAt?.time?.toDouble() ?: 0.0)
        }
    }

    /**
     * Convert a PaginatedEventList to a WritableMap for JS
     */
    fun paginatedEventListToJS(response: PaginatedEventList): WritableMap {
        return Arguments.createMap().apply {
            putArray("items", socialEventsToJSArray(response.items))
            putInt("total", response.total)
            putInt("skip", response.skip)
            putInt("limit", response.limit)
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
     * Convert a ReadableMap to CreateEventRequest
     */
    fun readableMapToCreateEventRequest(map: ReadableMap): CreateEventRequest {
        return CreateEventRequest(
            title = map.getString("title") ?: "",
            description = map.getString("description"),
            imageUrl = map.getString("imageUrl"),
            startTime = map.getDouble("startTime").toLong().let { Date(it) },
            endTime = map.getDouble("endTime").toLong().let { Date(it) },
            status = map.getString("status")?.let { EventStatus.valueOf(it) } ?: EventStatus.DRAFT,
            eventType = EventType.SOCIAL
        )
    }

    /**
     * Convert a ReadableMap to UpdateEventRequest
     */
    fun readableMapToUpdateEventRequest(map: ReadableMap): UpdateEventRequest {
        return UpdateEventRequest(
            title = map.getString("title"),
            description = map.getString("description"),
            imageUrl = map.getString("imageUrl"),
            startTime = map.getDouble("startTime").toLong().let { Date(it) },
            endTime = map.getDouble("endTime").toLong().let { Date(it) },
            status = map.getString("status")?.let { EventStatus.valueOf(it) } ?: EventStatus.DRAFT,
            eventType = EventType.SOCIAL
        )
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
            putDouble("createdAt", contact.createdAt?.time?.toDouble() ?: 0.0)
            putDouble("updatedAt", contact.updatedAt?.time?.toDouble() ?: 0.0)
        }
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
}
