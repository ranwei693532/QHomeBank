/**
 * @file      main.cpp
 * @brief     
 * @details   
 * @author    RW
 * @version     
 * @date      2020/8/19 0:46:18:45
 * @copyright RW
 * @par         (c) COPYRIGHT 2010-2018 by RW Systems, Inc.    
 *                        All rights reserved.
 *                                                                    
 *       This software is confidential and proprietary to RW 
 *     Systems, Inc.  No part of this software may be reproduced,    
 *     stored, transmitted, disclosed or used in any form or by any means
 *     other than as expressly provided by the written license agreement    
 *     between RW Systems and its licensee.
 * @par History      
 *         1.Date         -- 2020/8/19 0:46:18:45
 *           Author       -- RW
 *           Modification -- Created file
 *
 */

#define  MAIN_GLOBAL

/* includes-------------------------------------------------------------------*/
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <glog/logging.h>
#include <io.h>
#include <direct.h>
#include "main_win.hh"
#include "version.h"
#include "config.hh"
#include "db.hh"




    
/** @defgroup MAIN                                            
  * @brief MAIN system modules                                
  * @{                                                                         
  */
    
/* Private typedef&macro&definde----------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
                                                                                
/** @defgroup MAIN_Private_Functions                          
  * @{                                                                         
  */     

static void __Log_Init(const char* appname){
    char currentPath[1024] = {0};
    char logPath[1024] = {0};

    _getcwd(currentPath, sizeof(currentPath));
    sprintf(logPath, "%s\\logs\\", currentPath);
    if(_access(logPath, F_OK) != 0){
        _mkdir(logPath);
    }
    qDebug() << "logPath=" << logPath;
    FLAGS_colorlogtostderr = true;
    FLAGS_alsologtostderr = true;
    std::string logPathString = logPath;
    std::string logfileprefix = logPathString + "fatal-";
    google::SetLogDestination(google::GLOG_FATAL, logfileprefix.c_str());
    logfileprefix = logPathString + "error-";
    google::SetLogDestination(google::GLOG_ERROR, logfileprefix.c_str());
    logfileprefix = logPathString + "warning-";
    google::SetLogDestination(google::GLOG_WARNING, logfileprefix.c_str());
    logfileprefix = logPathString + "info-";
    google::SetLogDestination(google::GLOG_INFO, logfileprefix.c_str());
    google::InitGoogleLogging(appname);
    google::SetLogFilenameExtension(".log");
    FLAGS_logbufsecs = 0;
}

                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/** @defgroup MAIN_Functions                          
  * @{                                                                         
  */    

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    __Log_Init(argv[0]);
    LOG(INFO) << APP_NAME << "-v" << APP_VERSION << " running......";

    if (!QSqlDatabase::drivers().contains("QSQLITE")){
        QMessageBox::critical(nullptr, "Unable to load database", "This APP needs the SQLITE driver");
        return -1;
    } 
    
    CMainWin w;
    w.show();
    return a.exec();
}

                                                                                
/**                                                                             
  * @}                                                                         
  */	                                                                        
                                                                                
/**                                                                             
  * @}                                                                         
  */
                                                                                
/*************** (C) COPYRIGHT 2010-2018 RW ***********END OF FILE*************/







