package com.contactsmanagerrn

import android.Manifest
import android.content.pm.PackageManager
import androidx.core.content.ContextCompat
import com.facebook.react.bridge.*
import com.facebook.react.modules.core.PermissionListener
import io.contactsmanager.api.ContactsAuthorizationService

class RNContactsAuthorizationService(private val reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext), PermissionListener {

    private var currentPromise: Promise? = null
    private val PERMISSION_REQUEST_CODE = 1

    override fun getName(): String {
        return "RNContactsAuthorizationService"
    }

    @ReactMethod
    fun requestContactsAccess(promise: Promise) {
        currentPromise = promise
        val service = ContactsAuthorizationService.getInstance(reactContext)

        when {
            ContextCompat.checkSelfPermission(
                reactContext,
                Manifest.permission.READ_CONTACTS
            ) == PackageManager.PERMISSION_GRANTED -> {
                val response = Arguments.createMap().apply {
                    putBoolean("granted", true)
                }
                promise.resolve(response)
            }
            else -> {
                reactContext.addPermissionListener(this)
                service.requestContactsAccess()
            }
        }
    }

    @ReactMethod
    fun contactsAccessStatus(promise: Promise) {
        val service = ContactsAuthorizationService.getInstance(reactContext)
        val status = service.contactsAccessStatus()
        promise.resolve(status.ordinal)
    }

    @ReactMethod
    fun checkAccessStatus(promise: Promise) {
        val authService = ContactsAuthorizationService.getInstance(reactContext)
        val status = authService.checkAccessStatus()
        promise.resolve(status.ordinal)
    }

    @ReactMethod
    fun hasContactsReadAccess(promise: Promise) {
        val authService = ContactsAuthorizationService.getInstance(reactContext)
        val hasAccess = authService.hasContactsReadAccess()
        promise.resolve(hasAccess)
    }

    @ReactMethod
    fun shouldShowSettingsAlert(promise: Promise) {
        val activity = currentActivity ?: run {
            promise.reject("no_activity", "Activity not available")
            return
        }

        val authService = ContactsAuthorizationService.getInstance(reactContext)
        val shouldShow = authService.shouldShowSettingsAlert(activity)
        promise.resolve(shouldShow)
    }

    @ReactMethod
    fun showSettingsAlertView(promise: Promise) {
        val activity = currentActivity ?: run {
            promise.reject("no_activity", "Activity not available")
            return
        }

        val authService = ContactsAuthorizationService.getInstance(reactContext)
        authService.showSettingsAlertView(activity)
        promise.resolve(null)
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<String>,
        grantResults: IntArray
    ): Boolean {
        if (requestCode == PERMISSION_REQUEST_CODE) {
            val granted = grantResults.isNotEmpty() &&
                    grantResults[0] == PackageManager.PERMISSION_GRANTED

            val response = Arguments.createMap().apply {
                putBoolean("granted", granted)
            }
            currentPromise?.resolve(response)
            currentPromise = null
            return true
        }
        return false
    }
}
