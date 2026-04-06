export class HeroSection
{
  render(): string
  {
    return `
      <div class="text-center mb-12 md:mb-16">
        <h1 class="text-6xl font-bold text-white mb-8">
          🏓 Pong 3D
        </h1>
        <p class="text-xl text-white text-opacity-90 mb-8 max-w-4xl mx-auto leading-relaxed px-4">
          Discover the ultimate Pong game with local multiplayer, remote play, and tournaments.
        </p>
      </div>
    `;
  }
}