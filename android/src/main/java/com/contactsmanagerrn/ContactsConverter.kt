package com.contactsmanagerrn

import com.facebook.react.bridge.Arguments
import com.facebook.react.bridge.ReadableArray
import com.facebook.react.bridge.WritableArray
import com.facebook.react.bridge.WritableMap
import io.contactsmanager.api.models.*
import java.util.*

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
            putInt("contactType", contact.contactType)
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
            contact.birthday?.let { putDouble("birthday", it.time.toDouble()) }

            // Image data
            putString("imageUrl", contact.imageUrl)
            putString("imageData", contact.imageData?.let { String(it) })
            putString("thumbnailImageData", contact.thumbnailImageData?.let { String(it) })
            putBoolean("imageDataAvailable", contact.imageDataAvailable)

            // Extra data
            putArray("interests", stringListToJSArray(contact.interests))
            putArray("avatars", stringListToJSArray(contact.avatars))

            // Sync information
            putBoolean("isDeleted", contact.isDeleted)
            putDouble("dirtyTime", contact.dirtyTime)
            putDouble("lastSyncedAt", contact.lastSyncedAt)

            // Additional properties
            putString("contactSection", contact.contactSection)
            putString("matchString", contact.matchString)
            putString("parentContactId", contact.parentContactId)
            putString("sourceId", contact.sourceId)
            putDouble("createdAt", contact.createdAt)
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
            putString("contactId", contact.identifier)
            putString("sourceContactId", contact.identifier)
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
            putString("id", contact.identifier)
            putString("userId", contact.identifier)
            putString("displayName", contact.identifier)
            putString("givenName", contact.identifier)
            putString("familyName", contact.identifier)
            putString("username", contact.identifier)
            putString("avatarUrl", contact.avatarUrl)
            putString("bio", contact.identifier)
            putDouble("createdAt", System.currentTimeMillis().toDouble())
            putDouble("updatedAt", System.currentTimeMillis().toDouble())
        }
    }

    // Helper methods for converting contact details to JS arrays

    private fun phoneNumbersToJSArray(phoneNumbers: List<CMContactPhoneNumber>): WritableArray {
        val array = Arguments.createArray()
        phoneNumbers.forEach { phone ->
            val map = Arguments.createMap().apply {
                putString("contactId", phone.contactId)
                putString("value", phone.value)
                putString("label", phone.contactId)
                putString("type", phone.contactId)
            }
            array.pushMap(map)
        }
        return array
    }

    private fun emailAddressesToJSArray(emails: List<CMContactEmailAddress>): WritableArray {
        val array = Arguments.createArray()
        emails.forEach { email ->
            val map = Arguments.createMap().apply {
                putString("contactId", email.contactId)
                putString("value", email.value)
                putString("label", email.contactId)
                putString("type", email.contactId)
            }
            array.pushMap(map)
        }
        return array
    }

    private fun addressesToJSArray(addresses: List<CMContactAddress>): WritableArray {
        val array = Arguments.createArray()
        addresses.forEach { address ->
            val map = Arguments.createMap().apply {
                putString("contactId", address.contactId)
                putString("street", address.street)
                putString("city", address.city)
                putString("state", address.state)
                putString("postalCode", address.postalCode)
                putString("country", address.country)
                putString("label", address.contactId)
                putString("type", address.contactId)
            }
            array.pushMap(map)
        }
        return array
    }

    private fun datesToJSArray(dates: List<CMContactDate>): WritableArray {
        val array = Arguments.createArray()
        dates.forEach { date ->
            val map = Arguments.createMap().apply {
                putString("contactId", date.contactId)
                putDouble("date", date.date.time.toDouble())
                putString("label", date.contactId)
                putString("type", date.contactId)
            }
            array.pushMap(map)
        }
        return array
    }

    private fun urlsToJSArray(urls: List<CMContactURL>): WritableArray {
        val array = Arguments.createArray()
        urls.forEach { url ->
            val map = Arguments.createMap().apply {
                putString("contactId", url.contactId)
                putString("value", url.url)
                putString("label", url.contactId)
                putString("type", url.contactId)
            }
            array.pushMap(map)
        }
        return array
    }

    private fun socialProfilesToJSArray(profiles: List<CMContactSocialProfile>): WritableArray {
        val array = Arguments.createArray()
        profiles.forEach { profile ->
            val map = Arguments.createMap().apply {
                putString("contactId", profile.contactId)
                putString("value", profile.username)
                putString("label", profile.contactId)
                putString("type", profile.contactId)
            }
            array.pushMap(map)
        }
        return array
    }

    private fun relationsToJSArray(relations: List<CMContactRelation>): WritableArray {
        val array = Arguments.createArray()
        relations.forEach { relation ->
            val map = Arguments.createMap().apply {
                putString("contactId", relation.contactId)
                putString("name", relation.name)
                putString("label", relation.contactId)
                putString("type", relation.contactId)
            }
            array.pushMap(map)
        }
        return array
    }

    private fun instantMessagesToJSArray(ims: List<CMContactInstantMessage>): WritableArray {
        val array = Arguments.createArray()
        ims.forEach { im ->
            val map = Arguments.createMap().apply {
                putString("contactId", im.contactId)
                putString("value", im.username)
                putString("label", im.contactId)
                putString("type", im.contactId)
            }
            array.pushMap(map)
        }
        return array
    }

    private fun stringListToJSArray(strings: List<String>): WritableArray {
        val array = Arguments.createArray()
        strings.forEach { array.pushString(it) }
        return array
    }
}
