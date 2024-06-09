#!/bin/sh

##
# Fires an error handler when an error occurs depending on the errno
# value.
##
function error_handler() {
	last_errno="${1}"
	error_message="${2}"	

	if [ "${last_errno}" -ne 0 ]; then
		echo "${error_message}"
		return "${last_errno}"
	fi
}

##
# Creates a dir at '/opt/electrostatic-sandbox/'.
##
function prepare_sandbox() {
	sandbox_path="${1}"
	user_permissions="${2}"
	more_options="${3}"
	sudo mkdir --parents --mode="${user_permissions}" "${sandbox_path}"

	error_handler "$?" "Preparing sandbox ${sandbox_path} has failed!"
}

##
# Downloads a package from world-wide-web into Downloads dir.
##
function download_package() {
	download_dir="${1}"
	package_url="${2}"
	more_options="${3}"

	wget --https-only --continue --quiet --server-response "${package_url}" -P "${download_dir}"

	error_handler "$?" "Downloading package ${package_url} has failed!"
}

##
# Extracts a package content into the sandbox.
##
function tar_extract_package() {
	package_path="${1}"
	destination_path="${2}"

	sudo tar -xf "${package_path}" -C "${destination_path}"

	error_handler "$?" "Extracting package ${package_path} has failed!"
}

##
# Inserts a package (directory entry) into the sandbox directory.
##
function insert_package() {
	package_path="${1}"
	destination_path="${2}"
	
	sudo mv "${package_path}" "${destination_path}"
	
	error_handler "$?" "Extracting package ${package_path} has failed!"
}

##
# Extracts a zip package content into the sandbox.
##
function zip_extract_package() {
	package_path="${1}"
	destination_path="${2}"

	sudo unzip "${package_path}"

	insert_package "${package_path}" "${destination_path}"

	error_handler "$?" "Extracting package ${package_path} has failed!"
}	

##
# Creates a symbolic link (shortcut) to the binary.
##
function create_sandbox_symbol() {
	file_path="${1}"
	symbolic_link="${2}"

	sudo ln --verbose -s "${file_path}" "${symbolic_link}"

	error_handler "$?" "Symbolic link for ${file_path} has failed!"
}

##
# Deletes a symbolic link.
##
function delete_sandbox_symbol() {
	symbolic_link="${1}"
	sudo unlink "${symbolic_link}"
}
