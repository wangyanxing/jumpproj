//
//  JsonWriter.cpp
//  jumpproj
//
//  Created by Yanxing Wang on 2/1/16.
//
//

#include "JsonWriter.h"
#include "JsonFormat.h"

#include <fstream>
#include <iostream>

using namespace std;
using namespace rapidjson;
USING_NS_CC;

JsonWriter::JsonWriter() {
  mWriter.SetIndent(' ', 2);
  mWriter.StartObject();
}

JsonWriter::~JsonWriter() {
}

void JsonWriter::save(const std::string& fileName) {
  mWriter.EndObject();
//  std::ofstream file(fileName);
//  file << mBuffer.GetString();
  cout << mBuffer.GetString() << endl;
}

void JsonWriter::writeTime() {
  time_t rawtime;
  struct tm *ptm;
  time(&rawtime);
  ptm = gmtime(&rawtime);
  string timestr = asctime(ptm);
  timestr.resize(timestr.size() - 1);

  mWriter.String(MAP_TIME);
  mWriter.String(timestr);
}

void JsonWriter::writeAuthor() {
  string author = "unknown";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
  TCHAR username[UNLEN + 1];
  DWORD size = UNLEN + 1;
  GetUserName((TCHAR *) username, &size);
  author = username;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
  author = getlogin();
#endif

  mWriter.String(MAP_AUTHOR);
  mWriter.String(author);
}
