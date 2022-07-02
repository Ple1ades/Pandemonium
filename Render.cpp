#include "Utilities.h"

namespace Render{
    static SDL_Window* CreateCenteredWindow(uint32_t width, uint32_t height, std::string title)
    {
        // Get current device's Display Mode to calculate window position
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);

        // Calculate where the upper-left corner of a centered window will be
        const int32_t x = DM.w / 2 - width / 2;
        const int32_t y = DM.h / 2 - height / 2;

        // Create the SDL window
        SDL_Window* pWindow = SDL_CreateWindow(g_kWindowTitle, x, y, width, height,
            SDL_WINDOW_ALLOW_HIGHDPI);

        (e(!pWindow, "Failed to create Window\n"));

        return pWindow;
    }

    // Create SDL renderer and configure whether or not to use Hardware Acceleration
    static SDL_Renderer* CreateRenderer(SDL_Window* pWindow, bool hardwareAccelerated)
    {
        if (hardwareAccelerated)
            return SDL_CreateRenderer(pWindow, g_kRenderDeviceFlags, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        else
            return SDL_CreateRenderer(pWindow, g_kRenderDeviceFlags, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC );
    }

    // Create an SDL Texture to use as a "back buffer"
    static SDL_Texture* CreateBackBufferTexture(SDL_Renderer* pRenderer)
    {
        SDL_Texture* pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_ARGB8888, 
            SDL_TEXTUREACCESS_STREAMING, g_kRenderWidth, g_kRenderHeight);

        (e(!pTexture, "Failed to create Back Buffer Texture\n"));

        return pTexture;
    }

    // Free resources 
    static void Shutdown(SDL_Window** ppWindow, SDL_Renderer** ppRenderer, SDL_Texture** ppTexture)
    {
        // Free the Back Buffer
        if (ppTexture)
        {
            SDL_DestroyTexture(*ppTexture);
            *ppTexture = nullptr;
        }

        // Free the SDL renderer
        if (ppRenderer)
        {
            SDL_DestroyRenderer(*ppRenderer);
            *ppRenderer = nullptr;
        }

        // Free the SDL window
        if (ppWindow)
        {
            SDL_DestroyWindow(*ppWindow);
            *ppWindow = nullptr;
        }
    }

    // Initialize SDL Components 
    static int32_t Startup(SDL_Window** ppWindow, SDL_Renderer** ppRenderer, SDL_Texture** ppTexture)
    {
        SDL_Init(SDL_INIT_VIDEO);

        if (e(!ppWindow, "Potiner to Window* was null\n")) return -1;

        *ppWindow = CreateCenteredWindow(g_kWindowWidth, g_kWindowHeight, g_kWindowTitle);

        if (e(!*ppWindow, "No Window. Aborting..."))
        {
            Shutdown(ppWindow, ppRenderer, ppTexture);

            return -1;
        }

        if (e(!ppRenderer, "Pointer to Renderer* was null\n")) return -1;

        *ppRenderer = CreateRenderer(*ppWindow, true);

        if (e(!ppRenderer, "No Renderer. Aborting..."))
        {
            Shutdown(ppWindow, ppRenderer, ppTexture);

            return -1;
        }

        if (e(!ppTexture, "Pointer to Texture* was null\n")) return -1;

        *ppTexture = CreateBackBufferTexture(*ppRenderer);

        if (e(!*ppTexture, "No back buffer Texture. Aborting..."))
        {
            Shutdown(ppWindow, ppRenderer, ppTexture);

            return -1;
        }

        return 0;
    }

    


    // Call this within every render loop
    static int32_t RenderTexture(SDL_Window* pWindow, SDL_Renderer* pRenderer, SDL_Texture* pTexture, uint32_t* pTempPixelBuffer)
    {
        // The Back Buffer texture may be stored with an extra bit of width (pitch) on the video card in order to properly
        // align it in VRAM should the width not lie on the correct memory boundary (usually four bytes).
        int32_t pitch = 0;

        // This will hold a pointer to the memory position in VRAM where our Back Buffer texture lies
        uint32_t* pPixelBuffer = nullptr;

        // Lock the memory in order to write our Back Buffer image to it
        if (!SDL_LockTexture(pTexture, NULL, (void**)&pPixelBuffer, &pitch))
        {
            // The pitch of the Back Buffer texture in VRAM must be divided by four bytes
            // as it will always be a multiple of four
            pitch /= sizeof(uint32_t);

            // Fill texture with randomly colored pixels
            for (uint32_t i = 0; i < g_kRenderWidth * g_kRenderHeight; ++i)
                pPixelBuffer[i] = pTempPixelBuffer[i];

            // Unlock the texture in VRAM to let the GPU know we are done writing to it
            SDL_UnlockTexture(pTexture);

            // Copy our texture in VRAM to the display framebuffer in VRAM
            SDL_RenderCopy(pRenderer, pTexture, NULL, NULL);

            // Copy the VRAM framebuffer to the display
            SDL_RenderPresent(pRenderer);

            return 0;
        }
        else
            return g_kErrorOccurred;
    }

};