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
            putBoolean("alreadyFollowing", response.alreadyFollowing ?: false)
            putBoolean("wasFollowing", response.wasFollowing ?: false)
            putBoolean("success", response.success ?: false)
        }
    }

    /**
     * Convert a FollowStatusResponse to a WritableMap for JS
     */
    fun followStatusResponseToJS(response: FollowStatusResponse): WritableMap {
        return Arguments.createMap().apply {
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
            putInt("totalCount", response.totalCount)
        }
    }

    /**
     * Convert a PaginatedFollowList to a WritableMap for mutual followers
     */
    fun paginatedMutualFollowersToJS(response: PaginatedMutualFollowers): WritableMap {
        return Arguments.createMap().apply {
            putArray("items", canonicalContactsToJSArray(response.items))
            putInt("total", response.total)
            putInt("skip", response.skip)
            putInt("limit", response.limit)
            putInt("totalCount", response.totalCount)
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
            putString("followerId", relationship.followerId)
            putString("followedId", relationship.followedId)
            putString("userId", relationship.userId)
            putMap("follower", relationship.follower?.let { canonicalContactToJS(it) })
            putMap("followed", relationship.followed?.let { canonicalContactToJS(it) })
            putMap("localContact", relationship.localContact?.let { contactToJS(it) })
            putDouble("createdAt", relationship.createdAt?.time?.toDouble() ?: 0.0)
        }
    }

    /**
     * Convert a EventActionResponse to a WritableMap for JS
     */
    fun eventActionResponseToJS(response: EventActionResponse): WritableMap {
        return Arguments.createMap().apply {
            putString("eventId", response.eventId)
            putBoolean("created", response.created ?: false)
            putBoolean("updated", response.updated ?: false)
            putBoolean("deleted", response.deleted ?: false)
        }
    }

    /**
     * Convert a SocialEvent to a WritableMap for JS
     */
    fun socialEventToJS(event: SocialEvent): WritableMap {
        return Arguments.createMap().apply {
            putString("id", event.id)
            putString("organizationId", event.organizationId)
            putString("canonicalContactId", event.canonicalContactId)
            putString("eventType", event.eventType)
            putString("title", event.title)
            putString("description", event.description)
            putString("location", event.location)
            putDouble("startTime", event.startTime?.time?.toDouble() ?: 0.0)
            putDouble("endTime", event.endTime?.time?.toDouble() ?: 0.0)
            putMap("metadata", event.metadata?.let { mapToWritableMap(it) })
            putBoolean("isPublic", event.isPublic)
            putDouble("createdAt", event.createdAt?.time?.toDouble() ?: 0.0)
            putDouble("updatedAt", event.updatedAt?.time?.toDouble() ?: 0.0)
            putString("userId", event.userId)
            putMap("createdBy", event.createdBy?.let { creatorToJS(it) })
        }
    }

    private fun creatorToJS(creator: EventCreator): WritableMap {
        return Arguments.createMap().apply {
            putString("name", creator.name)
            putString("avatarUrl", creator.avatarUrl)
        }
    }

    private fun mapToWritableMap(map: Map<String, String>): WritableMap {
        return Arguments.createMap().apply {
            map.forEach { (key, value) -> putString(key, value) }
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
            putInt("totalCount", response.totalCount)
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
            eventType = map.getString("eventType") ?: "",
            title = map.getString("title") ?: "",
            description = map.getString("description"),
            location = map.getString("location"),
            startTime = map.getDouble("startTime").toLong().let { Date(it) },
            endTime = map.getDouble("endTime").toLong().let { Date(it) },
            metadata = map.getMap("metadata")?.let { readableMapToStringMap(it) },
            isPublic = map.getBoolean("isPublic")
        )
    }

    /**
     * Convert a ReadableMap to UpdateEventRequest
     */
    fun readableMapToUpdateEventRequest(map: ReadableMap): UpdateEventRequest {
        return UpdateEventRequest(
            title = map.getString("title"),
            description = map.getString("description"),
            location = map.getString("location"),
            startTime = map.getDouble("startTime").toLong().let { Date(it) },
            endTime = map.getDouble("endTime").toLong().let { Date(it) },
            metadata = map.getMap("metadata")?.let { readableMapToStringMap(it) },
            isPublic = if (map.hasKey("isPublic")) map.getBoolean("isPublic") else null
        )
    }

    private fun readableMapToStringMap(map: ReadableMap): Map<String, String> {
        val result = mutableMapOf<String, String>()
        map.toHashMap().forEach { (key, value) ->
            if (value != null) {
                result[key] = value.toString()
            }
        }
        return result
    }

    /**
     * Convert a CanonicalContact to a WritableMap for JS
     */
    fun canonicalContactToJS(contact: CanonicalContact): WritableMap {
        return Arguments.createMap().apply {
            putString("id", contact.id)
            putString("organizationId", contact.organizationId)
            putString("organizationUserId", contact.organizationUserId)
            putString("email", contact.email)
            putString("phone", contact.phone)
            putString("fullName", contact.fullName)
            putString("avatarUrl", contact.avatarUrl)
            putBoolean("isActive", contact.isActive ?: false)
            putDouble("createdAt", contact.createdAt?.time?.toDouble() ?: 0.0)
            putDouble("updatedAt", contact.updatedAt?.time?.toDouble() ?: 0.0)
            putMap("contactMetadata", contact.contactMetadata?.let { mapToWritableMap(it as Map<String, String>) })
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

    // Helper method for converting CMContact to JS - implementation needed
    private fun contactToJS(contact: CMContact): WritableMap {
        // TODO: Implement CMContact to JS conversion
        return Arguments.createMap()
    }
}
