package com.contactsmanagerrn

import android.app.Activity
import android.content.pm.PackageManager
import com.facebook.react.bridge.*
import com.facebook.react.modules.core.PermissionAwareActivity
import com.facebook.react.modules.core.PermissionListener
import io.contactsmanager.api.ContactAuthorizationService
import io.contactsmanager.api.ContactsAccessStatus

class RNContactsAuthorizationService(private val reactContext: ReactApplicationContext) :
    ReactContextBaseJavaModule(reactContext), PermissionListener {

    private var pendingPromise: Promise? = null
    private val PERMISSION_REQUEST_CODE = 1001

    override fun getName(): String {
        return "RNContactsAuthorizationService"
    }

    @ReactMethod
    fun requestContactsAccess(promise: Promise) {
        val activity = currentActivity ?: run {
            val response = Arguments.createMap().apply {
                putBoolean("granted", false)
                putInt("status", 0) // Equivalent to ContactsAccessStatusNotDetermined
                putString("error", "Activity not available")
            }
            promise.resolve(response)
            return
        }

        pendingPromise = promise

        val authService = ContactAuthorizationService.getInstance(reactContext)
        authService.requestAccess(activity) { status, exception ->
            val granted = status == ContactsAccessStatus.AUTHORIZED ||
                         status == ContactsAccessStatus.LIMITED_AUTHORIZED

            val response = Arguments.createMap().apply {
                putBoolean("granted", granted)
                putInt("status", status.ordinal)
                exception?.let { putString("error", it.message) }
            }

            pendingPromise?.resolve(response)
            pendingPromise = null
        }
    }

    @ReactMethod
    fun checkAccessStatus(promise: Promise) {
        val authService = ContactAuthorizationService.getInstance(reactContext)
        val status = authService.checkAccessStatus()
        promise.resolve(status.ordinal)
    }

    @ReactMethod
    fun hasContactsReadAccess(promise: Promise) {
        val authService = ContactAuthorizationService.getInstance(reactContext)
        val hasAccess = authService.hasContactsReadAccess()
        promise.resolve(hasAccess)
    }

    @ReactMethod
    fun shouldShowSettingsAlert(promise: Promise) {
        val activity = currentActivity ?: run {
            promise.reject("no_activity", "Activity not available")
            return
        }

        val authService = ContactAuthorizationService.getInstance(reactContext)
        val shouldShow = authService.shouldShowSettingsAlert(activity)
        promise.resolve(shouldShow)
    }

    @ReactMethod
    fun showSettingsAlertView(promise: Promise) {
        val activity = currentActivity ?: run {
            promise.reject("no_activity", "Activity not available")
            return
        }

        val authService = ContactAuthorizationService.getInstance(reactContext)
        authService.showSettingsAlertView(activity)
        promise.resolve(null)
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ): Boolean {
        if (requestCode == PERMISSION_REQUEST_CODE) {
            val authService = ContactAuthorizationService.getInstance(reactContext)
            val promise = pendingPromise

            if (promise != null) {
                authService.handlePermissionsResult(requestCode, grantResults) { status, exception ->
                    val granted = status == ContactsAccessStatus.AUTHORIZED ||
                                 status == ContactsAccessStatus.LIMITED_AUTHORIZED

                    val response = Arguments.createMap().apply {
                        putBoolean("granted", granted)
                        putInt("status", status.ordinal)
                        exception?.let { putString("error", it.message) }
                    }

                    promise.resolve(response)
                    pendingPromise = null
                }
                return true
            }
        }
        return false
    }
}
