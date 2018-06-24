::@echo off 

::@for /d /r %%c in (Listings) do @if exist %%c ( rd /s /q "%%c" & echo     É¾³ýÄ¿Â¼%%c) 
::@for /d /r %%c in (Objects) do @if exist %%c ( rd /s /q "%%c" & echo     É¾³ýÄ¿Â¼%%c) 
@for /d /r %%c in (.svn) do @if exist %%c ( rd /s /q "%%c" & echo     É¾³ýÄ¿Â¼%%c)  


::@for /r %%c in (*.uvopt) do  ( del   "%%c" & echo     É¾³ýÎÄ¼þ%%c)  
@for /d %%c in (Listings) do @if exist %%c (rd /s /q "%%c" & echo     É¾³ýÄ¿Â¼%%c)  
@for /d %%c in (Objects) do @if exist %%c (rd /s /q "%%c" & echo     É¾³ýÄ¿Â¼%%c)  
@for /r  %%c in (*.uvgui.* ) do del "%%c"
::pause