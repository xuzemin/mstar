
echo on
rem convert file extension
for /R ..\..\ %%f in (*.c) do copy "%%f" "%%fpp"
for /R ..\..\ %%f in (*.c) do del "%%f"
