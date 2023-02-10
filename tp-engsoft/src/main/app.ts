import type { Express } from 'express'

export default class App {
  app: Express
  constructor(app: Express) {
    this.app = app
  }
  public setupRoutes() {
  }
  public run() {
    this.app.listen(3000, () =>
      console.log('🚀 Server ready at: http://localhost:3000')
    )
  }
}
