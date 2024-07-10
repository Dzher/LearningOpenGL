#include "material.h"

using namespace utils;

MaterialFactory::MaterialFactory(KindsOfMaterial material_kind) : kind_(material_kind)
{
    switch (kind_)
    {
        case KindsOfMaterial::emerald:
        {
            material_.ambient_rgb = {0.0215, 0.1745, 0.0215};
            material_.diffuse_rgb = {0.07568, 0.61424, 0.07568};
            material_.specular_rgb = {0.633, 0.727811, 0.633};
            material_.specular_shininess = 0.6;
        }
        case KindsOfMaterial::jade:
        {
            material_.ambient_rgb = {0.135, 0.2225, 0.1575};
            material_.diffuse_rgb = {0.54, 0.89, 0.63};
            material_.specular_rgb = {0.316228, 0.316228, 0.316228};
            material_.specular_shininess = 0.1;
        }
        case KindsOfMaterial::obsidian:
        {
            material_.ambient_rgb = {0.05375, 0.05, 0.06625};
            material_.diffuse_rgb = {0.18275, 0.17, 0.22525};
            material_.specular_rgb = {0.332741, 0.328634, 0.346435};
            material_.specular_shininess = 0.3;
        }
        case KindsOfMaterial::pearl:
        {
            material_.ambient_rgb = {0.25, 0.20725, 0.20725};
            material_.diffuse_rgb = {1, 0.829, 0.829};
            material_.specular_rgb = {0.296648, 0.296648, 0.296648};
            material_.specular_shininess = 0.088;
        }
        case KindsOfMaterial::ruby:
        {
            material_.ambient_rgb = {0.1745, 0.01175, 0.01175};
            material_.diffuse_rgb = {0.61424, 0.04136, 0.04136};
            material_.specular_rgb = {0.727811, 0.626959, 0.626959};
            material_.specular_shininess = 0.6;
        }
        case KindsOfMaterial::turquoise:
        {
            material_.ambient_rgb = {0.1, 0.18725, 0.1745};
            material_.diffuse_rgb = {0.396, 0.74151, 0.69102};
            material_.specular_rgb = {0.297254, 0.30829, 0.306678};
            material_.specular_shininess = 0.1;
        }
        case KindsOfMaterial::brass:
        {
            material_.ambient_rgb = {0.329412, 0.223529, 0.027451};
            material_.diffuse_rgb = {0.780392, 0.568627, 0.113725};
            material_.specular_rgb = {0.992157, 0.941176, 0.807843};
            material_.specular_shininess = 0.21794872;
        }
        case KindsOfMaterial::bronze:
        {
            material_.ambient_rgb = {0.2125, 0.1275, 0.054};
            material_.diffuse_rgb = {0.714, 0.4284, 0.18144};
            material_.specular_rgb = {0.393548, 0.271906, 0.166721};
            material_.specular_shininess = 0.2;
        }
        case KindsOfMaterial::chrome:
        {
            material_.ambient_rgb = {0.25, 0.25, 0.25};
            material_.diffuse_rgb = {0.4, 0.4, 0.4};
            material_.specular_rgb = {0.774597, 0.774597, 0.774597};
            material_.specular_shininess = 0.6;
        }
        case KindsOfMaterial::copper:
        {
            material_.ambient_rgb = {0.19125, 0.0735, 0.0225};
            material_.diffuse_rgb = {0.7038, 0.27048, 0.0828};
            material_.specular_rgb = {0.256777, 0.137622, 0.086014};
            material_.specular_shininess = 0.1;
        }
        case KindsOfMaterial::gold:
        {
            material_.ambient_rgb = {0.24725, 0.1995, 0.0745};
            material_.diffuse_rgb = {0.75164, 0.60648, 0.22648};
            material_.specular_rgb = {0.628281, 0.555802, 0.366065};
            material_.specular_shininess = 0.4;
        }
        case KindsOfMaterial::silver:
        {
            material_.ambient_rgb = {0.19225, 0.19225, 0.19225};
            material_.diffuse_rgb = {0.50754, 0.50754, 0.50754};
            material_.specular_rgb = {0.508273, 0.508273, 0.508273};
            material_.specular_shininess = 0.4;
        }
        case KindsOfMaterial::blackPlastic:
        {
            material_.ambient_rgb = {0.0, 0.0, 0.0};
            material_.diffuse_rgb = {0.01, 0.01, 0.01};
            material_.specular_rgb = {0.50, 0.50, 0.50};
            material_.specular_shininess = .25;
        }
        case KindsOfMaterial::cyanPlastic:
        {
            material_.ambient_rgb = {0.0, 0.1, 0.06};
            material_.diffuse_rgb = {0.0, 0.50980392, 0.50980392};
            material_.specular_rgb = {0.50196078, 0.50196078, 0.50196078};
            material_.specular_shininess = .25;
        }
        case KindsOfMaterial::greenPlastic:
        {
            material_.ambient_rgb = {0.0, 0.0, 0.0};
            material_.diffuse_rgb = {0.1, 0.35, 0.1};
            material_.specular_rgb = {0.45, 0.55, 0.45};
            material_.specular_shininess = .25;
        }
        case KindsOfMaterial::redPlastic:
        {
            material_.ambient_rgb = {0.0, 0.0, 0.0};
            material_.diffuse_rgb = {0.5, 0.0, 0.0};
            material_.specular_rgb = {0.7, 0.6, 0.6};
            material_.specular_shininess = .25;
        }
        case KindsOfMaterial::whitePlastic:
        {
            material_.ambient_rgb = {0.0, 0.0, 0.0};
            material_.diffuse_rgb = {0.55, 0.55, 0.55};
            material_.specular_rgb = {0.70, 0.70, 0.70};
            material_.specular_shininess = .25;
        }
        case KindsOfMaterial::yellowPlastic:
        {
            material_.ambient_rgb = {0.0, 0.0, 0.0};
            material_.diffuse_rgb = {0.5, 0.5, 0.0};
            material_.specular_rgb = {0.60, 0.60, 0.50};
            material_.specular_shininess = .25;
        }
        case KindsOfMaterial::blackRubber:
        {
            material_.ambient_rgb = {0.02, 0.02, 0.02};
            material_.diffuse_rgb = {0.01, 0.01, 0.01};
            material_.specular_rgb = {0.4, 0.4, 0.4};
            material_.specular_shininess = .078125;
        }
        case KindsOfMaterial::cyanRubber:
        {
            material_.ambient_rgb = {0.0, 0.05, 0.05};
            material_.diffuse_rgb = {0.4, 0.5, 0.5};
            material_.specular_rgb = {0.04, 0.7, 0.7};
            material_.specular_shininess = .078125;
        }
        case KindsOfMaterial::greenRubber:
        {
            material_.ambient_rgb = {0.0, 0.05, 0.0};
            material_.diffuse_rgb = {0.4, 0.5, 0.4};
            material_.specular_rgb = {0.04, 0.7, 0.04};
            material_.specular_shininess = .078125;
        }
        case KindsOfMaterial::redRubber:
        {
            material_.ambient_rgb = {0.05, 0.0, 0.0};
            material_.diffuse_rgb = {0.5, 0.4, 0.4};
            material_.specular_rgb = {0.7, 0.04, 0.04};
            material_.specular_shininess = .078125;
        }
        case KindsOfMaterial::whiteRubber:
        {
            material_.ambient_rgb = {0.05, 0.05, 0.05};
            material_.diffuse_rgb = {0.5, 0.5, 0.5};
            material_.specular_rgb = {0.7, 0.7, 0.7};
            material_.specular_shininess = .078125;
        }
        case KindsOfMaterial::yellowRubber:
        {
            material_.ambient_rgb = {0.05, 0.05, 0.0};
            material_.diffuse_rgb = {0.5, 0.5, 0.4};
            material_.specular_rgb = {0.7, 0.7, 0.04};
            material_.specular_shininess = .078125;
        }
    }
}