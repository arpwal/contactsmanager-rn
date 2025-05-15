package com.contactsmanagerrn

import com.facebook.react.bridge.Arguments
import com.facebook.react.bridge.ReadableArray
import com.facebook.react.bridge.WritableArray
import com.facebook.react.bridge.WritableMap
import io.contactsmanager.api.models.CMContact
import io.contactsmanager.api.models.ContactRecommendation
import io.contactsmanager.api.models.LocalCanonicalContact
import io.contactsmanager.api.models.CanonicalContact

/**
 * Utility class for converting between native contact objects and JS objects
 */
object ContactsConverter {

    /**
     * Convert a list of CMContact objects to a WritableArray for JS
     */
    fun toJSArray(contacts: List<CMContact>): WritableArray {
        val array = Arguments.createArray()
        contacts.forEach { contact ->
            array.pushMap(toJS(contact))
        }
        return array
    }

    /**
     * Convert a CMContact to a WritableMap for JS
     */
    fun toJS(contact: CMContact): WritableMap {
        return Arguments.createMap().apply {
            putString("identifier", contact.identifier)
            putString("displayName", contact.displayName)

            // Basic information
            putInt("contactType", contact.contactType ?: 0)
            putString("namePrefix", contact.namePrefix)
            putString("givenName", contact.givenName)
            putString("middleName", contact.middleName)
            putString("familyName", contact.familyName)
            putString("previousFamilyName", contact.previousFamilyName)
            putString("nameSuffix", contact.nameSuffix)
            putString("nickname", contact.nickname)

            // Organization details
            putString("organizationName", contact.organizationName)
            putString("departmentName", contact.departmentName)
            putString("jobTitle", contact.jobTitle)

            // Contact information collections
            putArray("phoneNumbers", phoneNumbersToJSArray(contact.phoneNumbers))
            putArray("emailAddresses", emailAddressesToJSArray(contact.emailAddresses))
            putArray("addresses", addressesToJSArray(contact.addresses))
            putArray("dates", datesToJSArray(contact.dates))
            putArray("urlAddresses", urlsToJSArray(contact.urlAddresses))
            putArray("socialProfiles", socialProfilesToJSArray(contact.socialProfiles))
            putArray("relations", relationsToJSArray(contact.relations))
            putArray("instantMessageAddresses", instantMessagesToJSArray(contact.instantMessageAddresses))

            // Additional information
            putString("notes", contact.notes)
            putString("bio", contact.bio)
            putString("location", contact.location)

            // Birthday
            contact.birthday?.let { putDouble("birthday", it.toDouble()) }

            // Image data
            putString("imageUrl", contact.imageUrl)
            putString("imageData", contact.imageData)
            putString("thumbnailImageData", contact.thumbnailImageData)
            putBoolean("imageDataAvailable", contact.imageDataAvailable ?: false)

            // Extra data
            putArray("interests", stringListToJSArray(contact.interests))
            putArray("avatars", avatarsToJSArray(contact.avatars))

            // Sync information
            putBoolean("isDeleted", contact.isDeleted)
            contact.dirtyTime?.let { putDouble("dirtyTime", it.toDouble()) }
            contact.lastSyncedAt?.let { putDouble("lastSyncedAt", it.toDouble()) }

            // Additional properties
            putString("contactSection", contact.contactSection ?: "")
            putString("matchString", contact.matchString ?: "")
            putString("parentContactId", contact.parentContactId)
            putString("sourceId", contact.sourceId)
            putDouble("createdAt", contact.createdAt?.toDouble() ?: 0.0)
        }
    }

    /**
     * Convert a list of ContactRecommendation objects to a WritableArray for JS
     */
    fun recommendationsToJSArray(recommendations: List<ContactRecommendation>): WritableArray {
        val array = Arguments.createArray()
        recommendations.forEach { recommendation ->
            array.pushMap(recommendationToJS(recommendation))
        }
        return array
    }

    /**
     * Convert a ContactRecommendation to a WritableMap for JS
     */
    fun recommendationToJS(recommendation: ContactRecommendation): WritableMap {
        return Arguments.createMap().apply {
            putMap("contact", recommendation.contact?.let { toJS(it) } ?: Arguments.createMap())
            putDouble("score", recommendation.score)
            putString("reason", recommendation.reason)
            putInt("type", recommendation.type.ordinal)
            putString("organizationUserId", recommendation.organizationUserId)
        }
    }

    /**
     * Convert a list of LocalCanonicalContact objects to a WritableArray for JS
     */
    fun localCanonicalContactsToJSArray(contacts: List<LocalCanonicalContact>): WritableArray {
        val array = Arguments.createArray()
        contacts.forEach { contact ->
            array.pushMap(localCanonicalContactToJS(contact))
        }
        return array
    }

    /**
     * Convert a LocalCanonicalContact to a WritableMap for JS
     */
    fun localCanonicalContactToJS(contact: LocalCanonicalContact): WritableMap {
        return Arguments.createMap().apply {
            putMap("contact", contact.contact?.let { toJS(it) } ?: Arguments.createMap())
            putString("contactId", contact.contactId)
            putString("sourceContactId", contact.sourceContactId)
            putMap("canonicalContact", canonicalContactToJS(contact.canonicalContact))
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

    // Helper methods for converting contact details to JS arrays

    private fun phoneNumbersToJSArray(phoneNumbers: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        phoneNumbers?.forEach { phone ->
            // Implementation depends on the actual type
            // This is a simplified version
            val map = Arguments.createMap().apply {
                putString("contactId", "")
                putString("value", phone.toString())
                putString("type", "")
                putString("emoji", "")
            }
            array.pushMap(map)
        }
        return array
    }

    private fun emailAddressesToJSArray(emails: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        emails?.forEach { email ->
            // Implementation depends on the actual type
            val map = Arguments.createMap().apply {
                putString("contactId", "")
                putString("value", email.toString())
                putString("type", "")
                putString("emoji", "")
            }
            array.pushMap(map)
        }
        return array
    }

    private fun addressesToJSArray(addresses: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        // Implementation depends on the actual type
        return array
    }

    private fun datesToJSArray(dates: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        // Implementation depends on the actual type
        return array
    }

    private fun urlsToJSArray(urls: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        // Implementation depends on the actual type
        return array
    }

    private fun socialProfilesToJSArray(profiles: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        // Implementation depends on the actual type
        return array
    }

    private fun relationsToJSArray(relations: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        // Implementation depends on the actual type
        return array
    }

    private fun instantMessagesToJSArray(ims: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        // Implementation depends on the actual type
        return array
    }

    private fun avatarsToJSArray(avatars: List<Any>?): WritableArray {
        val array = Arguments.createArray()
        // Implementation depends on the actual type
        return array
    }

    private fun stringListToJSArray(strings: List<String>?): WritableArray {
        val array = Arguments.createArray()
        strings?.forEach { array.pushString(it) }
        return array
    }
}
