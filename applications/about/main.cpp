#include <libsystem/BuildInfo.h>
#include <libwidget/Application.h>
#include <libwidget/Markup.h>
#include <libwidget/Widgets.h>

int main(int argc, char **argv)
{
    application_initialize(argc, argv);

    Window *window = window_create_from_file("/Applications/about/about.markup");

    Widget *system_image = nullptr;
    if ((system_image = window_get_widget_by_id(window, "system-image")))
    {
        if (theme_is_dark())
        {
            image_set_image(system_image, "/Applications/about/logo-white.png");
        }
        else
        {
            image_set_image(system_image, "/Applications/about/logo-black.png");
        }
    }

    Widget *version_label = nullptr;
    if ((version_label = window_get_widget_by_id(window, "version-label")))
    {
        label_set_text(version_label, __BUILD_GITREF__ "/" __BUILD_CONFIG__);
    }

    Widget *ok_button = nullptr;
    if ((ok_button = window_get_widget_by_id(window, "ok-button")))
    {
        ok_button->on(Event::ACTION, [](auto) {
            application_exit(0);
        });
    }

    window_show(window);

    return application_run();
}
