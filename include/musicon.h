/*
 * musicon.h
 * Controlador principal de la aplicacion. Su unica responsabilidad es la
 * navegacion de menus: presenta opciones y delega TODA la logica de negocio
 * en los managers especializados (CancionManager, PlaylistManager, etc.).
 */

#ifndef MUSICON_H
#define MUSICON_H

/** Clase principal: orquesta los menus y la sesion del usuario. */
class musicon {
    public:
        musicon();

        /** Punto de entrada: arranca el sistema en el menu de bienvenida. */
        void iniciarSistema();

    private:
        int  _idUsuarioLogueado;          // cfg::ID_ADMIN, cfg::ID_VISITANTE o id real
        char _nombreUsuarioLogueado[50];

        // --- Sesion ---
        void menuBienvenida();
        void login();

        // --- Menus principales segun rol ---
        void menuPrincipalAdmin();
        void menuPrincipalUsuario();

        // --- Submenus ---
        void menuCargas();
        void menuConfiguracion();
        void menuSuscriptores();
        void menuCanciones();
        void menuPlaylists();
        void menuArtistas();
        void menuGeneros();
        void menuReportes();

        // --- Acciones ---
        void registrarAcceso();
};

#endif // MUSICON_H
