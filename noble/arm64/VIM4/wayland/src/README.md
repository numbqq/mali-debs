When using the current libMali.so file on Ubuntu 24.04, the Xwayland, QTWebkit, libmutter and possibly other programs fails as they depend on the existence of gbm_bo_create_with_modifiers2 function in the libgbm.so implementation. As we use libMali to provide gbm implementation, and as it currently doesn't support that function, we fail to get the UI working. To resolve this issue, I have added a shim library that provides the missing function. The code for gbm_bo_create_with_modifiers2 is based on the fallback code from [Xwayland source code](https://gitlab.freedesktop.org/xorg/xserver/-/blob/master/hw/xwayland/xwayland-glamor-gbm.c?ref_type=heads#L355-383).

To compile the code, do

```
sudo apt-get install libdrm-dev patchelf

gcc -Wall -O2 -fpic -shared gbm_bo_create_with_modifiers2.c -o mali_shim.so
```

Then I have used patchelf to add mali_shim.so file as dependency for libMali.so. This ensures that we have a fallback implementation available at runtime for the missing function without having to patch any other programs.

```
patchelf --add-needed mali_shim.so libMali.so
```
