#pragma once

void menuSetup();
void menuLoad();
void menuReset();

String menuValueText();
String menuTitleText();

void menuGoClick();
void menuGoHold();
void menuUpClick();
void menuDownClick();

uint64_t getFanTimeout();
uint64_t getFanUserTimeout();
uint64_t getFanHoldTimeout();
uint64_t getFanRemoteTimeout();

uint64_t getMistTimeout();
uint64_t getMistUserTimeout();
uint64_t getMistHoldTimeout();
uint64_t getMistRemoteTimeout();
