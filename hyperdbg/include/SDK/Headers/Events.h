/**
 * @file Events.h
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief HyperDbg's SDK Headers for Events
 * @details This file contains definitions of event datatypes
 * @version 0.2
 * @date 2022-06-28
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#pragma once

//////////////////////////////////////////////////
//               Event Details                  //
//////////////////////////////////////////////////

/**
 * @brief enum to show type of all HyperDbg events
 *
 */
typedef enum _DEBUGGER_EVENT_TYPE_ENUM
{

    HIDDEN_HOOK_READ_AND_WRITE,
    HIDDEN_HOOK_READ,
    HIDDEN_HOOK_WRITE,

    HIDDEN_HOOK_EXEC_DETOURS,
    HIDDEN_HOOK_EXEC_CC,

    SYSCALL_HOOK_EFER_SYSCALL,
    SYSCALL_HOOK_EFER_SYSRET,

    CPUID_INSTRUCTION_EXECUTION,

    RDMSR_INSTRUCTION_EXECUTION,
    WRMSR_INSTRUCTION_EXECUTION,

    IN_INSTRUCTION_EXECUTION,
    OUT_INSTRUCTION_EXECUTION,

    EXCEPTION_OCCURRED,
    EXTERNAL_INTERRUPT_OCCURRED,

    DEBUG_REGISTERS_ACCESSED,

    TSC_INSTRUCTION_EXECUTION,
    PMC_INSTRUCTION_EXECUTION,

    VMCALL_INSTRUCTION_EXECUTION,

    CONTROL_REGISTER_MODIFIED,
    CONTROL_REGISTER_READ,

} DEBUGGER_EVENT_TYPE_ENUM;

/**
 * @brief Type of Actions
 *
 */
typedef enum _DEBUGGER_EVENT_ACTION_TYPE_ENUM
{
    BREAK_TO_DEBUGGER,
    RUN_SCRIPT,
    RUN_CUSTOM_CODE

} DEBUGGER_EVENT_ACTION_TYPE_ENUM;

/**
 * @brief Type of calling the event
 *
 */
typedef enum _DEBUGGER_EVENT_CALLING_STAGE_TYPE
{
    DEBUGGER_CALLING_STAGE_PRE_EVENT_EMULATION,
    DEBUGGER_CALLING_STAGE_POST_EVENT_EMULATION,

} DEBUGGER_EVENT_CALLING_STAGE_TYPE;

/**
 * @brief Type of handling !syscall or !sysret
 *
 */
typedef enum _DEBUGGER_EVENT_SYSCALL_SYSRET_TYPE
{
    DEBUGGER_EVENT_SYSCALL_SYSRET_SAFE_ACCESS_MEMORY = 0,
    DEBUGGER_EVENT_SYSCALL_SYSRET_HANDLE_ALL_UD      = 1,

} DEBUGGER_EVENT_SYSCALL_SYSRET_TYPE;

#define SIZEOF_DEBUGGER_MODIFY_EVENTS sizeof(DEBUGGER_MODIFY_EVENTS)

/**
 * @brief different types of modifing events request (enable/disable/clear)
 *
 */
typedef enum _DEBUGGER_MODIFY_EVENTS_TYPE
{
    DEBUGGER_MODIFY_EVENTS_QUERY_STATE,
    DEBUGGER_MODIFY_EVENTS_ENABLE,
    DEBUGGER_MODIFY_EVENTS_DISABLE,
    DEBUGGER_MODIFY_EVENTS_CLEAR,
} DEBUGGER_MODIFY_EVENTS_TYPE;

/**
 * @brief The status of triggering events
 *
 */
typedef enum _DEBUGGER_TRIGGERING_EVENT_STATUS_TYPE
{
    DEBUGGER_TRIGGERING_EVENT_STATUS_SUCCESSFUL_NO_INITIALIZED = 0,
    DEBUGGER_TRIGGERING_EVENT_STATUS_SUCCESSFUL                = 0,
    DEBUGGER_TRIGGERING_EVENT_STATUS_SUCCESSFUL_IGNORE_EVENT   = 1,
    DEBUGGER_TRIGGERING_EVENT_STATUS_DEBUGGER_NOT_ENABLED      = 2,
    DEBUGGER_TRIGGERING_EVENT_STATUS_INVALID_EVENT_TYPE        = 3,

} DEBUGGER_TRIGGERING_EVENT_STATUS_TYPE;

/**
 * @brief request for modifying events (enable/disable/clear)
 *
 */
typedef struct _DEBUGGER_MODIFY_EVENTS
{
    UINT64 Tag;          // Tag of the target event that we want to modify
    UINT64 KernelStatus; // Kerenl put the status in this field
    DEBUGGER_MODIFY_EVENTS_TYPE
    TypeOfAction;      // Determines what's the action (enable | disable | clear)
    BOOLEAN IsEnabled; // Determines what's the action (enable | disable | clear)

} DEBUGGER_MODIFY_EVENTS, *PDEBUGGER_MODIFY_EVENTS;

/**
 * @brief request for performing a short-circuiting event
 *
 */
typedef struct _DEBUGGER_SHORT_CIRCUITING_EVENT
{
    UINT64  KernelStatus;      // Kerenl put the status in this field
    BOOLEAN IsShortCircuiting; // Determines whether to perform short circuting (on | off)

} DEBUGGER_SHORT_CIRCUITING_EVENT, *PDEBUGGER_SHORT_CIRCUITING_EVENT;

/**
 * @brief request for performing a short-circuiting event
 *
 */
typedef struct _DEBUGGER_BROADCASTING_OPTIONS
{
    UINT64 OptionalParam1; // Optional parameter
    UINT64 OptionalParam2; // Optional parameter
    UINT64 OptionalParam3; // Optional parameter
    UINT64 OptionalParam4; // Optional parameter

} DEBUGGER_BROADCASTING_OPTIONS, *PDEBUGGER_BROADCASTING_OPTIONS;

//////////////////////////////////////////////////
//    Enums For Event And Debugger Resources    //
//////////////////////////////////////////////////

/**
 * @brief Things to consider when applying resources
 *
 */
typedef enum _PROTECTED_HV_RESOURCES_PASSING_OVERS
{
    //
    // for exception bitmap
    //
    PASSING_OVER_NONE                                  = 0,
    PASSING_OVER_UD_EXCEPTIONS_FOR_SYSCALL_SYSRET_HOOK = 1,
    PASSING_OVER_EXCEPTION_EVENTS,

    //
    // for external interupts-exitings
    //
    PASSING_OVER_INTERRUPT_EVENTS,

    //
    // for external rdtsc/p exitings
    //
    PASSING_OVER_TSC_EVENTS,

    //
    // for external mov to hardware debug registers exitings
    //
    PASSING_OVER_MOV_TO_HW_DEBUG_REGS_EVENTS,

    //
    // for external mov to control registers exitings
    //
    PASSING_OVER_MOV_TO_CONTROL_REGS_EVENTS,

} PROTECTED_HV_RESOURCES_PASSING_OVERS;

/**
 * @brief Type of protected (multi-used) resources
 *
 */
typedef enum _PROTECTED_HV_RESOURCES_TYPE
{
    PROTECTED_HV_RESOURCES_EXCEPTION_BITMAP,

    PROTECTED_HV_RESOURCES_EXTERNAL_INTERRUPT_EXITING,

    PROTECTED_HV_RESOURCES_RDTSC_RDTSCP_EXITING,

    PROTECTED_HV_RESOURCES_MOV_TO_DEBUG_REGISTER_EXITING,

    PROTECTED_HV_RESOURCES_MOV_CONTROL_REGISTER_EXITING,

    PROTECTED_HV_RESOURCES_MOV_TO_CR3_EXITING,

} PROTECTED_HV_RESOURCES_TYPE;
