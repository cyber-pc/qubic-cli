ARG base_image="ubuntu:22.04"
ARG image_type="release"
ARG package_location=""
ARG app_location="/qubic-cli"

# Set environment variables to avoid user prompts during installation
ARG DEBIAN_FRONTEND=noninteractive

#********************Setup an runtime environment for running.
# If this scale up, we will switch to dual images
FROM ${base_image} AS build_image_runtime
ARG DEBIAN_FRONTEND
ARG package_location

# Install runtime environment
RUN apt-get update && apt-get clean


#********************Setup an develop environment for building.
# If this scale up, we will switch to dual images
FROM ${base_image} AS build_image_develop
ARG DEBIAN_FRONTEND
ARG package_location
ARG app_location

# Install cmake, git and dev environments
RUN apt-get update && \
    apt-get install -y cmake build-essential && \
    apt-get clean

#********************Package
FROM ${base_image} AS build_image_release
ARG DEBIAN_FRONTEND
ARG APP_DEPENDENCIES
ARG package_location
ARG app_location

# Create and set the working directory
WORKDIR ${app_location}

# Copy the requirements.txt file
COPY ${package_location}/ ${app_location}/

# Place holder to trigger above build
FROM build_image_${image_type}
ARG DEBIAN_FRONTEND
ARG APP_DEPENDENCIES
ARG CMD_BUILD
ARG package_location
ARG app_location
