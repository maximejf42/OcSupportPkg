/** @file
  Copyright (C) 2016, The HermitCrabs Lab. All rights reserved.

  All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/

#include <Uefi.h>

#include <IndustryStandard/Pci.h>

#include <Guid/ApplePlatformInfo.h>

#include <Protocol/DataHub.h>
#include <Protocol/LegacyRegion.h>
#include <Protocol/PciIo.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/OcMiscLib.h>
#include <Library/OcStringLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Macros.h>

// LegacyRegionlock
/** Lock the legacy region specified to enable modification.

  @param[in] LegacyAddress  The address of the region to lock.
  @param[in] LegacyLength   The size of the region to lock.

  @retval EFI_SUCCESS  The region was locked successfully.
**/
EFI_STATUS
LegacyRegionLock (
  IN UINT32  LegacyAddress,
  IN UINT32  LegacyLength
  )
{
  EFI_STATUS                 Status;

  EFI_LEGACY_REGION_PROTOCOL *LegacyRegionProtocol;
  UINT32                     Granularity;

  LegacyRegionProtocol = NULL;
  Status               = gBS->LocateProtocol (
                                &gEfiLegacyRegionProtocolGuid,
                                NULL,
                                (VOID **) &LegacyRegionProtocol
                                );

  if (!EFI_ERROR (Status) && (LegacyRegionProtocol != NULL)) {
    // Lock Region Using LegacyRegionProtocol

    Granularity = 0;
    Status      = LegacyRegionProtocol->Lock (
                                          LegacyRegionProtocol,
                                          LegacyAddress,
                                          LegacyLength,
                                          &Granularity
                                          );
    DEBUG ((
      DEBUG_INFO,
      "Lock LegacyRegion 0x%0X-0x%0X - %r\n",
      LegacyAddress,
      (LegacyAddress + (LegacyLength - 1)),
      Status
      ));
  }

  return Status;
}
