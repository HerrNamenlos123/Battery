#pragma once

#include "Battery/pch.h"
#include "Battery/Platform/Platform.h"

namespace Battery {

	class File {

		std::string _path;
		std::string _content;
		bool valid = false;

	public:
		File() {
		}

		File(const std::string& p, const std::string& c, bool v) {
			_path = p;
			_content = c;
			valid = v;
		}

		bool fail() const {
			return !valid;
		}

		std::string content() const {
			return _content;
		}

		std::string path() const {
			return _path;
		}
	};

	/// <summary>
	/// Throws: 
	/// Battery::LockfileUnavailableException if the lockfile is already locked or
	/// Battery::NoSuchFileOrDirectoryException if the filename is invalid or contains directories
	/// </summary>
	class Lockfile {
	public:
		Lockfile(const std::string& file, bool createDirectories = false);
		~Lockfile();

	private:
		void* fileDescriptor = nullptr;
	};

	/// <summary>
	/// Check if a given filename exists on disk, can either be a directory or a file
	/// </summary>
	/// <param name="path">- path to check for, e.g. C:/some/file.txt</param>
	/// <returns>bool - exists or not</returns>
	bool FilenameExists(const std::string& path);

	/// <summary>
	/// Check if the given file exists on disk
	/// </summary>
	/// <param name="path">- The full or relative path</param>
	/// <returns>bool - is a valid file or not</returns>
	bool FileExists(const std::string& path);

	/// <summary>
	/// Check if the given directory exists on disk
	/// </summary>
	/// <param name="path">- The full or relative path</param>
	/// <returns>bool - is a valid directory or not</returns>
	bool DirectoryExists(const std::string& path);

	/// <summary>
	/// Get the content of a directory. Returns an array of filenames and directory names. Must be checked with
	/// FileExists() and DirectoryExists() to know whether it's a file or directory
	/// </summary>
	/// <param name="path">- The full or relative path</param>
	/// <returns>An array with all filenames and directory names</returns>
	std::vector<std::filesystem::path> GetDirectoryContent(const std::string& path);

	/// <summary>
	/// Create a new directory, parent directories are created as needed
	/// </summary>
	/// <param name="path">- The full or relative path</param>
	/// <returns>bool - true if creation was successful or the directory already existed</returns>
	bool MakeDirectory(const std::string& path);

	/// <summary>
	/// Update the name of a file on disk. Essentially equivalent to MoveFile().
	/// The file directory can change.
	/// </summary>
	bool RenameFile(const std::string& file, const std::string& targetFile);

	/// <summary>
	/// Move a file on disk by specifying the filename (absolute or relative path)
	/// and the target directory, which is created if it does not exist.
	/// </summary>
	bool MoveFile(const std::string& file, std::string directory);

	/// <summary>
	/// Move a directory on disk. Specify the source and target directory, all files inside the 
	/// source directory are moved into the target directory recursively.
	/// Directories are created as needed. If a file fails to be moved,
	/// the process is aborted and all files are left as-is.
	/// </summary>
	bool MoveDirectory(std::string source, std::string target);

	/// <summary>
	/// Load a file from memory and return it as a Battery::FileUtils::File class.
	/// File class contains the content with .str() and information if it failed with .fail().
	/// </summary>
	/// <param name="path">- The full or relative path</param>
	/// <returns>Battery::FileUtils::File - A File class</returns>
	Battery::File ReadFile(const std::string& path, bool binary = false);

	/// <summary>
	/// Write a file to memory at the given path. When the parent directory does not exist, it
	/// is created with PrepareDirectory()
	/// </summary>
	/// <param name="path">- The complete filename and path</param>
	/// <param name="content">- The content of the file</param>
	/// <returns>bool - if successful</returns>
	bool WriteFile(const std::string& path, const std::string& content, bool binary = false);

	/// <summary>
	/// Delete a file or empty directory from memory
	/// </summary>
	/// <param name="path">- The file to delete</param>
	/// <returns>bool - if deletion was successful</returns>
	bool RemoveFile(const std::string& path);

	/// <summary>
	/// Delete an entire directory, will recursively delete all files in it. 
	/// Will also return true when the directory does not exist, but also when 
	/// the given path is a file instead of a directory
	/// </summary>
	/// <param name="path">- The directory to delete</param>
	/// <returns>bool - if deletion was successful</returns>
	bool RemoveDirectory(const std::string& path);

	/// <summary>
	/// Delete the content of a directory, will recursively delete all files in it. 
	/// The parent directory is not deleted. Returns true if all content was successfully deleted,
	/// but returns false when the parent did not exist
	/// </summary>
	/// <param name="path">- The directory of which the content is to remove</param>
	/// <returns>bool - if content deletion was successful</returns>
	bool RemoveDirectoryContent(const std::string& path);

	/// <summary>
	/// Prepare an empty directory: Check if it exists, delete all content or create it, 
	/// so it's empty and ready to use
	/// </summary>
	/// <param name="path">- The directory to prepare</param>
	/// <returns>bool - if preparation was successful</returns>
	bool PrepareEmptyDirectory(const std::string& path);

	/// <summary>
	/// Prepare a directory: Check if it exists or create it, but it does not delete any content if
	/// it already exists
	/// </summary>
	/// <param name="path">- The directory to prepare</param>
	/// <returns>bool - if preparation was successful</returns>
	bool PrepareDirectory(const std::string& path);







	/// <summary>
	/// Open a windows file dialog to choose a file for saving. Returns the full path of the selected saving location
	/// or "" when no file was chosen
	/// </summary>
	/// <param name="acceptedFiles">- Filter of accepted file types, for example: { "*.*", "*.txt", "*.wav" }"</param>
	/// <param name="parentWindow">- An Window reference to the parent window</param>
	/// <param name="defaultLocation">- The default path at which the dialog starts when opened, "" for no default</param>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>std::string - The full path to the file chosen</returns>
	std::string PromptFileSaveDialog(const std::vector<std::string>& acceptedFilesArray,
		std::optional<sf::WindowHandle> parentWindow = std::nullopt,
		const std::string& defaultLocation = "");

	/// <summary>
	/// Open a windows file dialog to choose a file to load. Returns the full path of the selected loading location
	/// or "" when no file was chosen
	/// </summary>
	/// <param name="acceptedFiles">- Filter of accepted file types, for example: { "*.*", "*.txt", "*.wav" }</param>
	/// <param name="parentWindow">- An Window reference to the parent window</param>
	/// <param name="defaultLocation">- The default path at which the dialog starts when opened, "" for no default</param>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>std::string - The full path to the file chosen</returns>
	std::string PromptFileOpenDialog(const std::vector<std::string>& acceptedFilesArray,
		std::optional<sf::WindowHandle> parentWindow = std::nullopt,
		const std::string& defaultLocation = "");

	/// <summary>
	/// Open a windows file dialog to choose multiple files to load. Returns the full path of the selected loading location
	/// or "" when no file was chosen
	/// </summary>
	/// <param name="acceptedFiles">- Filter of accepted file types, for example: "*.*;*.txt;"</param>
	/// <param name="parentWindow">- An ALLEGRO_DISPLAY pointer to the parent window, nullptr if none</param>
	/// <param name="defaultLocation">- The default path at which the dialog starts when opened, "" for no default</param>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>std::vector&lt;std::string&gt; - An array of the files chosen</returns>
	std::vector<std::string> PromptFileOpenDialogMultiple(const std::vector<std::string>& acceptedFilesArray,
		std::optional<sf::WindowHandle> parentWindow = std::nullopt,
		const std::string& defaultLocation = "");

	/// <summary>
	/// Open a windows file dialog to choose a folder to load. Returns the full path of the selected loading location
	/// or "" when no folder was chosen
	/// </summary>
	/// 
	/// <param name="parentWindow">- An Window reference to the parent window</param>
	/// <param name="defaultLocation">- The default path at which the dialog starts when opened, "" for no default</param>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>std::string - The full path to the file chosen</returns>
	std::string PromptFileOpenDialogFolder(std::optional<sf::WindowHandle> parentWindow = std::nullopt,
		const std::string& defaultLocation = "");

	/// <summary>
	/// Save a file with a windows file dialog popup to choose the file location. When the file already exists, a dialog pops up. 
	/// When successfully saved, the full path of the just saved file is returned, otherwise nothing is returned (""). 
	/// When forceSave is true, the dialog is repeated until the file is saved, so this can be used when the file needs to be saved
	/// because the program needs to close
	/// </summary>
	/// <param name="extension">- The file extension, which will be added to the name, for example "txt"</param>
	/// <param name="fileContent">- The content of the file to save</param>
	/// <param name="parentWindow">- The Window reference to the parent window if one exists</param>
	/// <param name="defaultLocation">- The full path to the location when the dialog pops up</param>
	/// <param name="forceSave">- When true, the dialog is repeated and only returns when the file has been successfully saved</param>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>std::string - The full path to the saved file or ""</returns>
	std::string SaveFileWithDialog(const char* extension, const std::string& fileContent,
		std::optional<sf::WindowHandle> parentWindow = std::nullopt,
		const std::string& defaultLocation = "", bool forceSave = false);

	/// <summary>
	/// Load a file with a windows file dialog popup to choose the file location.
	/// When successfully loaded, a Battery::FileUtils::File class is returned, containing the content, the file location
	/// and information if it's valid. When it's not valid, either no file was chosen or it could not be loaded.
	/// </summary>
	/// <param name="extension">- The file extension, which will be added to the name, for example "txt"</param>
	/// <param name="parentWindow">- The ALLEGRO_DISPLAY pointer to the parent window if one exists</param>
	/// <param name="defaultLocation">- The full path to the location when the dialog pops up</param>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>File class - Containing information about the loaded file</returns>
	Battery::File LoadFileWithDialog(const char* extension,
		std::optional<sf::WindowHandle> parentWindow = std::nullopt,
		const std::string& defaultLocation = "");







	/// <summary>
	/// Get the full path of the currently running executable, for example "C:/some/path/main.exe"
	/// </summary>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>std::string - the full path or "" if invalid</returns>
	std::string GetExecutablePath();

	/// <summary>
	/// Get the name of the executable, for example "main.exe"
	/// </summary>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>std::string - the name or "" if invalid</returns>
	std::string GetExecutableName();

	/// <summary>
	/// Get the directory in which the executable is placed, for example "C:/some/path/" when
	/// the executable was "C:/some/path/main.exe"
	/// </summary>
	/// <exception cref="Battery::Exception - Thrown when Allegro was not initialized before this function call"></exception>
	/// <returns>std::string - the full path or "" if invalid</returns>
	std::string GetExecutableDirectory();







	/// <summary>
	/// Get the filename from a full path (file or directory), for example: Pass "C:/some/file.txt" and get "file.txt".
	/// Trailing forward '/'s are removed and treated as a file.
	/// </summary>
	/// <param name="path">- The full or relative path to process</param>
	/// <returns>std::string - Only the last part of the path</returns>
	std::string GetFilename(const std::string& path);

	/// <summary>
	/// Get the basename from a full path, for example: Pass "C:/some/file.txt" and get "file".
	/// Returns the full name of a directory.
	/// </summary>
	/// <param name="path">- The full or relative path to process</param>
	/// <returns>std::string - The basename</returns>
	std::string GetBasename(const std::string& path);

	/// <summary>
	/// Get the extension from a full path filename, for example: Pass "C:/some/multiple.dots.txt" and get ".txt".
	/// Returns none ("") if last filename does not contain a dot.
	/// </summary>
	/// <param name="path">- The full or relative path to process</param>
	/// <returns>std::string - The extension</returns>
	std::string GetExtension(const std::string& path);

	/// <summary>
	/// Get an array with every component of a path, for example: Pass "C:/some/file.txt" and get {"C:", "some", "file.txt"}
	/// or pass "../directory" and get {"..", "directory"}
	/// </summary>
	/// <param name="path">- The full or relative path to process</param>
	/// <returns>std::vector&lt;std::string&gt; - An array with every component</returns>
	std::vector<std::string> GetPathComponents(const std::string& path);

	/// <summary>
	/// Get the directory in which the target is lying, for example: "C:/some/file.txt" -> "C:/some/".
	/// Also works for folders.
	/// </summary>
	/// <param name="path">- The full or relative path to process</param>
	/// <returns>std::string - Basically the path without the filename</returns>
	std::string GetParentDirectory(const std::string& path);

	/// <summary>
	/// Get an Allegro standard path from al_get_standard_path(). Available paths are ALLEGRO_RESOURCES_PATH, ALLEGRO_TEMP_PATH, 
	/// ALLEGRO_USER_HOME_PATH, ALLEGRO_USER_DOCUMENTS_PATH, ALLEGRO_USER_DATA_PATH, ALLEGRO_USER_SETTINGS_PATH, ALLEGRO_EXENAME_PATH
	/// </summary>
	/// <param name="id">- An Allegro enum from above</param>
	/// <exception cref="Battery::Exception - Thrown when the given Allegro enum is invalid"></exception>
	/// <returns>std::string - The path returned from Allegro</returns>
	std::string GetAllegroStandardPath(int id);










	/// <summary>
	/// Execute shell commands (basic system() call)
	/// </summary>
	/// <param name="command"></param>
	/// <returns></returns>
	std::pair<bool, size_t> ExecuteShellCommand(const std::string& command);

	/// <summary>
	/// Execute shell commands in a separate process. Returns a pair of bool and a return code.
	/// If the command runs successfully, returns true and the exit code of the command.
	/// Otherwise, returns false and the error code of GetLastError() of ShellExecuteEx(). 
	/// Do not use this function to call processes that create windows.
	/// </summary>
	/// <param name="command"></param>
	/// <returns></returns>
	std::pair<bool, size_t> ExecuteShellCommandSilent(const std::string& command, bool hidden = true);







	/// <summary>
	/// Unzip a .zip file to a target directory using powershell Expand-Archive call.
	/// Existing files are overwritten by default. The target directory will be created as needed.
	/// </summary>
	bool ExtractArchive(const std::string& file, const std::string& targetDirectory, bool force = true);

	/// <summary>
	/// Load an embedded file from the resource compiler (.rc file). Parameter is the Win32 ID, 
	/// taken from 'resource.h'. Second parameter is the expected type from resource.rc ("ICON", "PNG", "FONT", ...)
	/// </summary>
	std::vector<uint8_t> LoadEmbeddedResource(int id, const char* type);

}
