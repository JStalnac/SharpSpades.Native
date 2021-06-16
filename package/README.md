# Creating a NuGet package

**Requires the NuGet CLI**

- Create directory `runtimes` and place binaries in their
respective folders.

Folder structure: `runtimes/<RID>/native/<binary>`

[.NET Runtime IDentifier catalog](https://docs.microsoft.com/en-us/dotnet/core/rid-catalog)

- Run `nuget pack`
